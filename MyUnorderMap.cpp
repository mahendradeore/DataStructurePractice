#include <iostream>
#include <vector>
#include <list>
#include <utility>

// Custom unordered_map implementation
template <typename K, typename V>
class MyUnorderedMap {
private:
    static const int INITIAL_SIZE = 16;
    std::vector<std::list<std::pair<K, V>>> buckets;
    int bucket_count;
    int size;
    
    int hashFunction(const K& key) const {
        return std::hash<K>{}(key) % bucket_count;
    }

public:
    MyUnorderedMap() : bucket_count(INITIAL_SIZE), size(0) {
        buckets.resize(bucket_count);
    }

    void insert(const K& key, const V& value) {
        int index = hashFunction(key);
        for (auto &pair : buckets[index]) {
            if (pair.first == key) {
                pair.second = value;  // Update value if key exists
                return;
            }
        }
        buckets[index].emplace_back(key, value);
        size++;
    }

    bool find(const K& key, V& value) const {
        int index = hashFunction(key);
        for (const auto &pair : buckets[index]) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }

    void erase(const K& key) {
        int index = hashFunction(key);
        auto &bucket = buckets[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                size--;
                return;
            }
        }
    }
    
    int getSize() const { return size; }
};

int main() {
    MyUnorderedMap<std::string, int> myMap;
    myMap.insert("Alice", 25);
    myMap.insert("Bob", 30);
    myMap.insert("Charlie", 22);

    int age;
    if (myMap.find("Bob", age)) {
        std::cout << "Bob's age: " << age << std::endl;
    }

    myMap.erase("Alice");
    if (!myMap.find("Alice", age)) {
        std::cout << "Alice not found in map.\n";
    }

    return 0;
}
