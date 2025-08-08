#include <iostream>
#include <string>

int main() {
    // Basic data types
    int age = 25;
    float pi = 3.14159f;
    char grade = 'A';
    bool isPassing = true;
    std::string name = "John";
    
    // Type inference
    auto autoInt = 42;              // Deduced as int
    auto autoDouble = 3.14;         // Deduced as double
    
    // Constants
    const int MAX_SCORE = 100;
    constexpr double GRAVITY = 9.81;
    
    // Initialization methods
    int direct(10);                 // Direct initialization
    int uniform{15};                // Uniform initialization (recommended)
    int copy = 20;                  // Copy initialization
    
    // Output
    std::cout << "Variables Demo:" << std::endl;
    std::cout << "Age: " << age << ", Grade: " << grade << std::endl;
    std::cout << "Pi: " << pi << ", Passing: " << std::boolalpha << isPassing << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Auto types - int: " << autoInt << ", double: " << autoDouble << std::endl;
    std::cout << "Constants - MAX_SCORE: " << MAX_SCORE << ", GRAVITY: " << GRAVITY << std::endl;
    
    // Scope demonstration
    {
        int localVar = 100;
        std::cout << "Block scope - localVar: " << localVar << std::endl;
    }   // localVar destroyed here
    
    return 0;
}