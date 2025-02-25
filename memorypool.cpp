#include <iostream>

class MemoryPool {
private:
    struct Block {
        size_t size;
        bool free;
        char* ptr;
        Block* next;  // Pointer to the next block
    };

    char* pool;
    size_t totalSize;
    Block* head;  // Head of the linked list

public:
    MemoryPool(size_t size) : totalSize(size) {
        pool = new char[size];
        head = new Block{size, true, pool, nullptr};  // Initially, the whole memory is free
    }

    ~MemoryPool() {
        delete[] pool;
        while (head) {
            Block* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void* allocate(size_t size) {
        Block* current = head;
        Block* prev = nullptr;

        while (current) {
            if (current->free && current->size >= size) {
                current->free = false;

                // Split block if there's extra space
                if (current->size > size) {
                    Block* newBlock = new Block{current->size - size, true, current->ptr + size, current->next};
                    current->size = size;
                    current->next = newBlock;
                }
                return current->ptr;
            }
            prev = current;
            current = current->next;
        }

        std::cerr << "MemoryPool: No sufficient memory available!\n";
        return nullptr;
    }

    void deallocate(void* ptr) {
        Block* current = head;
        while (current) {
            if (current->ptr == ptr) {
                current->free = true;
                mergeFreeBlocks();
                return;
            }
            current = current->next;
        }
        std::cerr << "MemoryPool: Invalid deallocation request!\n";
    }

    void mergeFreeBlocks() {
        Block* current = head;
        while (current && current->next) {
            if (current->free && current->next->free) {
                current->size += current->next->size;
                Block* temp = current->next;
                current->next = current->next->next;
                delete temp;
            } else {
                current = current->next;
            }
        }
    }

    void printPool() {
        std::cout << "Memory Pool Status:\n";
        Block* current = head;
        while (current) {
            std::cout << "[Size: " << current->size << ", Free: " 
                      << (current->free ? "Yes" : "No") << "]\n";
            current = current->next;
        }
        std::cout << "-----------------------\n";
    }
};

// Example Usage
int main() {
    MemoryPool pool(100);

    void* ptr1 = pool.allocate(20);
    void* ptr2 = pool.allocate(30);
    pool.printPool();

    pool.deallocate(ptr1);
    pool.printPool();

    void* ptr3 = pool.allocate(15);  // Should reuse freed space
    pool.printPool();

    pool.deallocate(ptr2);
    pool.deallocate(ptr3);
    pool.printPool();

    return 0;
}
