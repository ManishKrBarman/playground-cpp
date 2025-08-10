#include <iostream>
#include <vector>

int main() {
    std::cout << "Loops Demo:" << std::endl;
    
    // For loop
    std::cout << "\nFor loop (1-5): ";
    for (int i = 1; i <= 5; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // While loop
    std::cout << "While loop countdown: ";
    int count = 5;
    while (count > 0) {
        std::cout << count << " ";
        count--;
    }
    std::cout << std::endl;
    
    // Do-while loop
    std::cout << "Do-while loop: ";
    int num = 1;
    do {
        std::cout << num << " ";
        num++;
    } while (num <= 3);
    std::cout << std::endl;
    
    // Range-based for loop (C++11)
    std::vector<int> numbers = {10, 20, 30, 40, 50};
    std::cout << "Range-based for: ";
    for (const auto& n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // Break and continue
    std::cout << "Break/Continue demo: ";
    for (int i = 1; i <= 10; i++) {
        if (i == 3) continue;  // Skip 3
        if (i == 7) break;     // Stop at 7
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Nested loops
    std::cout << "Nested loops (multiplication table 2x2):" << std::endl;
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            std::cout << i << "x" << j << "=" << (i*j) << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}