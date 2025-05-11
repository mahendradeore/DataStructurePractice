#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
// Step 1: Define your custom struct
struct PersonName {
    std::string first;
    std::string last;

    // Step 2: Define operator== so unordered_map can compare keys
    bool operator==(const PersonName& other) const {
        return first == other.first && last == other.last;
    }
};

// Step 3: Provide a custom hash function for PersonName
namespace std {
    template <>
    struct hash<PersonName> {
        std::size_t operator()(const PersonName& p) const {
            std::hash<std::string> hasher;
            return hasher(p.first) ^ (hasher(p.last) << 1); // Combine hashes
        }
    };
}

int cstring_hash(const std::string& str) {
    int hash = 5381;  // Magic prime number

    // Traverse the string using a while loop
    int i = 0;
    while (str[i] != '\0') {
        hash = ((hash << 5) + hash) + str[i];  // hash * 33 + c
        i++;
    }

    return hash;
}

int main() {
    std::unordered_map<PersonName, int> people;

    people[{ "Alice", "Smith" }] = 1;
    people[{ "Bob", "Jones" }] = 2;

    for (const auto& entry : people) {
        std::cout << entry.first.first << " " << entry.first.last
                  << " : " << entry.second << '\n';
    }
    string str("mahensra");
    cout << "hash  = " << cstring_hash(str)<<endl;

    return 0;
}
