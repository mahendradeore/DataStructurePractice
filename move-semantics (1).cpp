#include <iostream>
#include <string>

class mymove {
    int a;
    std::string* name;  // Dynamically allocated memory for the name

public:
    // Constructor
    mymove(int val, const std::string& nm): a(val), name(new std::string(nm)) {
        std::cout << "Constructor called: a = " << a << ", name = " << *name << std::endl;
    }

    // Destructor
    ~mymove() {
        delete name;  // Free allocated memory
        std::cout << "Destructor called for: a = " << a << std::endl;
    }

    // Copy Constructor (Deep Copy)
    mymove(const mymove& other) :a(other.a), name(new std::string(*other.name)) {
        std::cout << "Copy Constructor called: a = " << a << ", name = " << *name << std::endl;
    }

    // Move Constructor
    mymove(mymove&& other) noexcept: a(other.a), name(other.name) {
        other.name = nullptr;  // Nullify the source's pointer
        std::cout << "Move Constructor called: a = " << a << std::endl;
    }

    // Copy Assignment Operator
    mymove& operator=(const mymove& other) {
        if (this != &other) {  // Self-assignment check
            delete name;  // Free existing memory
            a = other.a;
            name = new std::string(*other.name);  // Deep copy the string
        }
        std::cout << "Copy Assignment Operator called: a = " << a << ", name = " << *name << std::endl;
        return *this;
    }

    // Move Assignment Operator
    mymove& operator=(mymove&& other) noexcept {
        if (this != &other) {  // Self-assignment check
            delete name;  // Free existing memory
            a = other.a;
            name = other.name;  // Transfer ownership of the pointer
            other.name = nullptr;  // Nullify the source's pointer
        }
        std::cout << "Move Assignment Operator called: a = " << a << std::endl;
        return *this;
    }

    // Print details of the object
    void print() const {
        if (name) {
            std::cout << "a = " << a << ", name = " << *name << std::endl;
        } else {
            std::cout << "a = " << a << ", name = nullptr" << std::endl;
        }
    }
};

int main() {
    mymove obj1(10, "Alice");
    mymove obj2(20, "Bob");

    obj1.print();
    obj2.print();

    // Copy Assignment
    obj1 = obj2;
    obj1.print();

    // Move Assignment
    mymove obj3(30, "Charlie");
    obj3 = std::move(obj1);
    obj3.print();
    obj1.print();  // After move, obj1's resources are nullified

    // Copy Constructor
    mymove obj4 = obj3;
    obj4.print();

    // Move Constructor
    mymove obj5 = std::move(obj3);
    obj5.print();
    obj3.print();  // After move, obj3's resources are nullified

    return 0;
}
