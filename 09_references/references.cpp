#include <iostream>
#include <string>

// Function using references
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function with const reference (efficient for large objects)
void printString(const std::string& str) {
    std::cout << "String: " << str << std::endl;
    // str cannot be modified due to const
}

// Function returning reference
int& getArrayElement(int arr[], int index) {
    return arr[index];  // Returns reference to array element
}

int main() {
    std::cout << "References Demo:" << std::endl;
    
    // Basic reference
    int value = 42;
    int& ref = value;  // ref is an alias for value
    
    std::cout << "value = " << value << std::endl;
    std::cout << "ref = " << ref << std::endl;
    
    // Modifying through reference
    ref = 100;
    std::cout << "After ref = 100, value = " << value << std::endl;
    
    // Both point to same memory address
    std::cout << "Address of value: " << &value << std::endl;
    std::cout << "Address of ref: " << &ref << std::endl;
    
    // Function with references
    int x = 10, y = 20;
    std::cout << "\nBefore swap: x = " << x << ", y = " << y << std::endl;
    swap(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    
    // Const reference
    std::string message = "Hello, World!";
    printString(message);  // No copying - efficient
    
    // Reference to array element
    int arr[] = {1, 2, 3, 4, 5};
    int& element = getArrayElement(arr, 2);  // Reference to arr[2]
    std::cout << "arr[2] = " << element << std::endl;
    
    element = 99;  // Modifies arr[2]
    std::cout << "After element = 99, arr[2] = " << arr[2] << std::endl;
    
    // Range-based for with references
    std::cout << "Doubling array elements: ";
    for (int& elem : arr) {
        elem *= 2;  // Modify original elements
    }
    
    for (const int& elem : arr) {  // Read-only access
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    return 0;
}