#include <iostream>
#include <unordered_map>
#include <list>

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, int>> cacheList;  // Doubly linked list (stores key-value pairs)
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap; // Hash map (key -> list iterator)

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end())
            return -1;  // Key not found

        // Move the accessed node to the front (most recently used)
        auto it = cacheMap[key];
        cacheList.splice(cacheList.begin(), cacheList, it);

        return it->second;
    }

    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            // Update existing key, move to front
            auto it = cacheMap[key];
            it->second = value;
            cacheList.splice(cacheList.begin(), cacheList, it);
            return;
        }

        if (cacheList.size() >= capacity) {
            // Remove the least recently used item (back of the list)
            int lruKey = cacheList.back().first;
            cacheMap.erase(lruKey);
            cacheList.pop_back();
        }

        // Insert new key-value pair at the front
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }

    void printCache() {
        std::cout << "Cache: ";
        for (const auto& [key, value] : cacheList) {
            std::cout << "(" << key << "," << value << ") ";
        }
        std::cout << "\n";
    }
};

// Example usage
int main() {
    LRUCache cache(3);  // Cache of capacity 3

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.printCache();  // (3,30) (2,20) (1,10)

    std::cout << "Get 2: " << cache.get(2) << "\n";  // Moves (2,20) to front
    cache.printCache();  // (2,20) (3,30) (1,10)

    cache.put(4, 40);  // Evicts LRU (1,10)
    cache.printCache();  // (4,40) (2,20) (3,30)

    std::cout << "Get 1: " << cache.get(1) << "\n";  // -1 (not found)

    return 0;
}
