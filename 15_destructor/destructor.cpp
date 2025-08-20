#include <iostream>
#include <string>
#include <memory>

// Basic destructor example
class BasicResource {
private:
    std::string name;
    int* data;

public:
    BasicResource(const std::string& n, int size) : name(n) {
        data = new int[size];
        std::cout << "BasicResource '" << name << "' created" << std::endl;
    }
    
    // Destructor
    ~BasicResource() {
        delete[] data;
        std::cout << "BasicResource '" << name << "' destroyed" << std::endl;
    }
    
    void setData(int index, int value) {
        data[index] = value;
    }
};

// Virtual destructor example
class Base {
public:
    Base() {
        std::cout << "Base constructor" << std::endl;
    }
    
    // Virtual destructor - ensures proper cleanup in inheritance
    virtual ~Base() {
        std::cout << "Base destructor" << std::endl;
    }
};

class Derived : public Base {
private:
    int* buffer;

public:
    Derived() : Base() {
        buffer = new int[100];
        std::cout << "Derived constructor" << std::endl;
    }
    
    ~Derived() override {
        delete[] buffer;
        std::cout << "Derived destructor" << std::endl;
    }
};

// RAII (Resource Acquisition Is Initialization) pattern
class FileManager {
private:
    std::string filename;
    FILE* file;

public:
    FileManager(const std::string& name) : filename(name), file(nullptr) {
        file = fopen(filename.c_str(), "w");
        if (file) {
            std::cout << "File '" << filename << "' opened successfully" << std::endl;
        } else {
            std::cout << "Failed to open file '" << filename << "'" << std::endl;
        }
    }
    
    ~FileManager() {
        if (file) {
            fclose(file);
            std::cout << "File '" << filename << "' closed" << std::endl;
        }
    }
    
    void write(const std::string& content) {
        if (file) {
            fputs(content.c_str(), file);
        }
    }
    
    // Delete copy constructor and assignment to prevent double-free
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
};

// Stack unwinding demonstration
class StackDemo {
private:
    std::string name;

public:
    StackDemo(const std::string& n) : name(n) {
        std::cout << "StackDemo '" << name << "' created" << std::endl;
    }
    
    ~StackDemo() {
        std::cout << "StackDemo '" << name << "' destroyed" << std::endl;
    }
};

void demonstrateStackUnwinding() {
    StackDemo obj1("First");
    StackDemo obj2("Second");
    
    std::cout << "About to throw exception..." << std::endl;
    throw std::runtime_error("Demo exception");
    
    // This line won't execute, but destructors will still be called
    std::cout << "This won't print" << std::endl;
}

// Exception-safe class
class SafeResource {
private:
    int* data;
    size_t size;

public:
    SafeResource(size_t s) : size(s) {
        data = new(std::nothrow) int[size];
        if (!data) {
            throw std::bad_alloc();
        }
        std::cout << "SafeResource created with " << size << " elements" << std::endl;
    }
    
    // Destructor should never throw exceptions
    ~SafeResource() noexcept {
        delete[] data;
        std::cout << "SafeResource destroyed" << std::endl;
    }
};

int main() {
    std::cout << "Destructors Demo:" << std::endl;
    
    // Basic destructor usage
    {
        BasicResource resource("TestResource", 10);
        resource.setData(0, 42);
        std::cout << "Resource in use..." << std::endl;
    } // Destructor called automatically here
    
    std::cout << "\n--- Virtual Destructor ---" << std::endl;
    
    // Virtual destructor ensures proper cleanup
    Base* basePtr = new Derived();
    delete basePtr;  // Both Derived and Base destructors called
    
    std::cout << "\n--- RAII Pattern ---" << std::endl;
    
    {
        FileManager fm("temp.txt");
        fm.write("Hello, RAII!");
        // File automatically closed when fm goes out of scope
    }
    
    std::cout << "\n--- Stack Unwinding ---" << std::endl;
    
    try {
        demonstrateStackUnwinding();
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n--- Exception Safety ---" << std::endl;
    
    try {
        SafeResource safe(1000);
        std::cout << "Safe resource created successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n--- Modern C++ Alternative (Smart Pointers) ---" << std::endl;
    
    {
        // Using smart pointers eliminates need for manual destructor
        auto smartPtr = std::make_unique<int[]>(10);
        std::cout << "Smart pointer manages memory automatically" << std::endl;
        // Memory automatically freed when smartPtr goes out of scope
    }
    
    std::cout << "\nProgram ending..." << std::endl;
    return 0;
}
