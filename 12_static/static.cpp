#include <iostream>
#include <string>

// Static global variable (internal linkage)
static int globalCounter = 0;

// Static function (internal linkage)
static void helperFunction() {
    std::cout << "Static helper function called" << std::endl;
}

class Counter {
private:
    static int objectCount;  // Static data member declaration
    int instanceId;

public:
    Counter() : instanceId(++objectCount) {
        std::cout << "Counter object #" << instanceId << " created" << std::endl;
    }
    
    ~Counter() {
        std::cout << "Counter object #" << instanceId << " destroyed" << std::endl;
    }
    
    // Static member function
    static int getObjectCount() {
        return objectCount;
        // Note: Cannot access non-static members from static function
    }
    
    void showInfo() const {
        std::cout << "Instance " << instanceId << " out of " << objectCount << " total" << std::endl;
    }
};

// Static data member definition (required outside class)
int Counter::objectCount = 0;

// Function demonstrating static local variable
void incrementalFunction() {
    static int callCount = 0;  // Initialized only once
    callCount++;
    std::cout << "This function has been called " << callCount << " times" << std::endl;
}

int main() {
    std::cout << "Static Demo:" << std::endl;
    
    // Static local variable in function
    std::cout << "\nStatic local variable:" << std::endl;
    incrementalFunction();
    incrementalFunction();
    incrementalFunction();
    
    // Static member functions and variables
    std::cout << "\nInitial object count: " << Counter::getObjectCount() << std::endl;
    
    {
        Counter obj1;
        Counter obj2;
        std::cout << "Object count after creating 2: " << Counter::getObjectCount() << std::endl;
        
        obj1.showInfo();
        obj2.showInfo();
    }  // Objects destroyed here
    
    std::cout << "Object count after destruction: " << Counter::getObjectCount() << std::endl;
    
    // Static global function
    helperFunction();
    
    return 0;
}