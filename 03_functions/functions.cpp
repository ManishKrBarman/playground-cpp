#include <iostream>
#include <string>

// Function prototypes
int add(int a, int b);
void greet(const std::string& name);
int multiply(int x, int y = 1);  // Default parameter
double divide(double a, double b);

// Function overloading
int max(int a, int b);
double max(double a, double b);

// Pass by reference
void increment(int& value);

// Recursive function
int factorial(int n);

int main() {
    // Basic function calls
    std::cout << "Functions Demo:" << std::endl;
    
    int sum = add(5, 3);
    std::cout << "5 + 3 = " << sum << std::endl;
    
    greet("Alice");
    
    // Default parameters
    std::cout << "multiply(5) = " << multiply(5) << std::endl;
    std::cout << "multiply(5, 3) = " << multiply(5, 3) << std::endl;
    
    // Function overloading
    std::cout << "max(10, 20) = " << max(10, 20) << std::endl;
    std::cout << "max(3.14, 2.71) = " << max(3.14, 2.71) << std::endl;
    
    // Pass by reference
    int value = 10;
    std::cout << "Before increment: " << value << std::endl;
    increment(value);
    std::cout << "After increment: " << value << std::endl;
    
    // Recursion
    std::cout << "factorial(5) = " << factorial(5) << std::endl;
    
    return 0;
}

// Function definitions
int add(int a, int b) {
    return a + b;
}

void greet(const std::string& name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}

int multiply(int x, int y) {
    return x * y;
}

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    }
    std::cout << "Error: Division by zero!" << std::endl;
    return 0.0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}

void increment(int& value) {
    value++;
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}