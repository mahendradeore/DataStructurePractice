#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>  // For uint8_t

#define POOL_SIZE 1024

typedef struct MemoryBlock {
    int size;
    bool isFree;
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct MemoryManager {
    void *memory_pool;
    MemoryBlock *current_node;
} MemoryManager;

MemoryManager *init_memory_pool(int size) {
    if (size <= sizeof(MemoryBlock)) return NULL;  // Ensure valid pool size

    MemoryManager *manager = (MemoryManager*)malloc(sizeof(MemoryManager));
    if (!manager) return NULL;

    manager->memory_pool = malloc(size);
    if (!manager->memory_pool) {
        free(manager);
        return NULL;
    }

    manager->current_node = (MemoryBlock*)manager->memory_pool;
    manager->current_node->size = size - sizeof(MemoryBlock);
    manager->current_node->isFree = true;
    manager->current_node->next = NULL;
    
    return manager;
}

void* pool_alloc(MemoryManager *manager, int size) {
    if (!manager || size <= 0) return NULL;

    MemoryBlock *block = manager->current_node;
    MemoryBlock *prev = NULL;

    // Find the first suitable free block
    while (block && (!block->isFree || block->size < size)) {
        block = block->next;
    }

    if (!block) return NULL;  // No suitable block found

    // Split the block if there's excess space
    if (block->size > size + sizeof(MemoryBlock)) {
        MemoryBlock *new_block = (MemoryBlock*)((uint8_t*)block + sizeof(MemoryBlock) + size);
        new_block->size = block->size - size - sizeof(MemoryBlock);
        new_block->isFree = true;
        new_block->next = block->next;
        block->size = size;
        block->next = new_block;
    }
    
    block->isFree = false;
    return (void*)((uint8_t*)block + sizeof(MemoryBlock));
}

void pool_free(MemoryManager *manager, void *ptr) {
    if (!manager || !ptr) return;

    MemoryBlock *block = (MemoryBlock*)((uint8_t*)ptr - sizeof(MemoryBlock));
    block->isFree = true;

    // Merge adjacent free blocks
    MemoryBlock *current = manager->current_node;
    while (current) {
        if (current->isFree && current->next && current->next->isFree) {
            current->size += sizeof(MemoryBlock) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void destroy_memory_pool(MemoryManager *mp) {
    if (!mp) return;
    free(mp->memory_pool);
    free(mp);
}

int main() {
    MemoryManager* pool = init_memory_pool(POOL_SIZE);
    if (!pool) {
        printf("Failed to initialize memory pool\n");
        return 1;
    }

    char* ptr1 = (char*)pool_alloc(pool, 8);
    int* ptr2 = (int*)pool_alloc(pool, 16);
    printf("Allocated memory at: %p (char[8]), %p (int[4])\n", ptr1, ptr2);

    pool_free(pool, ptr1);
    printf("Freed char[8]\n");

    int* ptr3 = (int*)pool_alloc(pool, 32);
    printf("Allocated memory at: %p (int[8])\n", ptr3);

    destroy_memory_pool(pool);
    printf("Memory pool destroyed\n");

    return 0;
}
