#include <iostream>

int main() {
    std::cout << "Pointers Demo:" << std::endl;
    
    // Basic pointer operations
    int value = 42;
    int* ptr = &value;  // ptr holds address of value
    
    std::cout << "value = " << value << std::endl;
    std::cout << "address of value (&value) = " << &value << std::endl;
    std::cout << "ptr = " << ptr << std::endl;
    std::cout << "value via ptr (*ptr) = " << *ptr << std::endl;
    
    // Modifying value through pointer
    *ptr = 100;
    std::cout << "After *ptr = 100, value = " << value << std::endl;
    
    // Pointer arithmetic
    int arr[] = {10, 20, 30, 40, 50};
    int* arrPtr = arr;  // Points to first element
    
    std::cout << "\nPointer arithmetic:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "arr[" << i << "] = " << *(arrPtr + i) << std::endl;
    }
    
    // Dynamic memory allocation
    int* dynamicPtr = new int(99);  // Allocate on heap
    std::cout << "\nDynamic value = " << *dynamicPtr << std::endl;
    delete dynamicPtr;  // Free memory
    dynamicPtr = nullptr;  // Good practice
    
    // Array on heap
    int size = 5;
    int* dynamicArray = new int[size];
    for (int i = 0; i < size; i++) {
        dynamicArray[i] = i * 10;
    }
    
    std::cout << "Dynamic array: ";
    for (int i = 0; i < size; i++) {
        std::cout << dynamicArray[i] << " ";
    }
    std::cout << std::endl;
    
    delete[] dynamicArray;  // Free array
    
    // Null pointer check
    int* nullPtr = nullptr;
    if (nullPtr == nullptr) {
        std::cout << "nullPtr is null" << std::endl;
    }
    
    return 0;
}