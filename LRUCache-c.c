#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 3  // Max LRU cache size
#define HEAP_SIZE 1000

typedef struct Node {
    int key;
    int value;
    struct Node *prev, *next;
} Node;

typedef struct LRUCache {
    int size;
    Node *head, *tail;
    Node *hashMap[HEAP_SIZE];  // Only store max CACHE_SIZE keys
} LRUCache;

// Initialize LRU Cache
LRUCache* createCache() {
    LRUCache *cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->size = 0;
    cache->head = cache->tail = NULL;
    for (int i = 0; i < HEAP_SIZE; i++) {
        cache->hashMap[i] = NULL;
    }
    return cache;
}

// Move Node to Head (Recently Used)
void moveToHead(LRUCache *cache, Node *node) {
    if (cache->head == node) return;
    
    // Remove node from current position
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (cache->tail == node) cache->tail = node->prev;

    // Move to head
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) cache->head->prev = node;
    cache->head = node;

    if (!cache->tail) cache->tail = node;
}

// Get value from cache
int get(LRUCache *cache, int key) {
    int index = key % HEAP_SIZE;
    Node *node = cache->hashMap[index];
    if (node && node->key == key) {
        moveToHead(cache, node);
        return node->value;
    }
    return -1;  // Not found
}

// Put value into cache
void put(LRUCache *cache, int key, int value) {
    int index = key % HEAP_SIZE;
    
    Node *node = cache->hashMap[index];
    if (node && node->key == key) {
        node->value = value;
        moveToHead(cache, node);
        return;
    }

    // Create new node
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->prev = newNode->next = NULL;

    // Add to head
    newNode->next = cache->head;
    if (cache->head) cache->head->prev = newNode;
    cache->head = newNode;
    if (!cache->tail) cache->tail = newNode;

    // Store in hashMap
    cache->hashMap[index] = newNode;
    cache->size++;

    // Remove least recently used if full
    if (cache->size > CACHE_SIZE) {
        int tailIndex = cache->tail->key % HEAP_SIZE;
        cache->hashMap[tailIndex] = NULL;
        Node *temp = cache->tail;
        cache->tail = cache->tail->prev;
        if (cache->tail) cache->tail->next = NULL;
        free(temp);
        cache->size--;
    }
}

void printCache(LRUCache *cache) {
    Node *node = cache->head;
    while (node) {
        printf("%d:%d ", node->key, node->value);
        node = node->next;
    }
    printf("\n");
}
// Main Function
int main() {
    LRUCache *cache = createCache();
    put(cache, 1, 100);
    put(cache, 2, 200);
    put(cache, 3, 300);
    printf("Get(1): %d\n", get(cache, 1)); // Moves key 1 to front
    put(cache, 4, 400); // Evicts LRU (key 2)
    printf("Get(2): %d\n", get(cache, 2)); // Should return -1 (not found)
    printf("Get(3): %d\n", get(cache, 3)); // Still in cache
    printf("Get(4): %d\n", get(cache, 4)); // Still in cache
    printCache(cache);
    put(cache, 100, 400);
    put(cache, 500, 40);
    printCache(cache);
    printf("Get(3): %d\n", get(cache,500 )); // Still in cache
    printf("Get(3): %d\n", get(cache, 100)); // Still in cache
    return 0;
}
