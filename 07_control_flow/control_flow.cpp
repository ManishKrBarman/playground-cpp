#include <iostream>
#include <stdexcept>

// Function to demonstrate return
int findFirstEven(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            return arr[i];  // Early return
        }
    }
    return -1;  // Not found
}

// Function to demonstrate exception handling
double divide(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero!");
    }
    return a / b;
}

int main() {
    std::cout << "Control Flow Demo:" << std::endl;
    
    // Return statement
    int numbers[] = {1, 3, 6, 7, 8};
    int firstEven = findFirstEven(numbers, 5);
    std::cout << "First even number: " << firstEven << std::endl;
    
    // Break in nested loops
    std::cout << "Breaking from nested loops:" << std::endl;
    bool found = false;
    for (int i = 1; i <= 3 && !found; i++) {
        for (int j = 1; j <= 3; j++) {
            std::cout << "(" << i << "," << j << ") ";
            if (i == 2 && j == 2) {
                std::cout << "Found target! ";
                found = true;
                break;  // Breaks inner loop only
            }
        }
        std::cout << std::endl;
    }
    
    // Exception handling
    try {
        double result1 = divide(10, 2);
        std::cout << "10 / 2 = " << result1 << std::endl;
        
        double result2 = divide(10, 0);  // This will throw
        std::cout << "This won't execute" << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    // Continue with skip pattern
    std::cout << "Numbers except multiples of 3: ";
    for (int i = 1; i <= 10; i++) {
        if (i % 3 == 0) {
            continue;  // Skip multiples of 3
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    return 0;
}