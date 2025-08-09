#include <iostream>
#include "math_utils.h"  // Include our custom header

int main() {
    std::cout << "Header Files Demo:" << std::endl;
    
    // Using functions from header
    int a = 10, b = 5;
    std::cout << a << " + " << b << " = " << add(a, b) << std::endl;
    std::cout << a << " - " << b << " = " << subtract(a, b) << std::endl;
    
    // Using inline function
    std::cout << "square(" << a << ") = " << square(a) << std::endl;
    
    // Using power function
    std::cout << "power(2, 3) = " << power(2.0, 3) << std::endl;
    
    // Using constant
    std::cout << "PI = " << PI << std::endl;
    
    return 0;
}