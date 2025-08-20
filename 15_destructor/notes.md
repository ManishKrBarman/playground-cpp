## 🧹 Destructors in C++

## 🎯 What are Destructors?

Destructors are **special member functions** that clean up objects when they are destroyed. They:
- Have the **same name** as the class prefixed with `~`
- **No parameters** and **no return type**
- **Automatically called** when object goes out of scope
- **Cannot be overloaded** (only one destructor per class)

```cpp
class MyClass {
public:
    ~MyClass() {  // Destructor
        // Cleanup code here
    }
};
```

## 🔧 When Destructors are Called

### Automatic Objects
```cpp
{
    MyClass obj;  // Constructor called
    // Use obj...
}  // Destructor called automatically when obj goes out of scope
```

### Dynamic Objects
```cpp
MyClass* ptr = new MyClass();  // Constructor called
delete ptr;                    // Destructor called explicitly
```

### Stack Unwinding
```cpp
void function() {
    MyClass obj1;
    MyClass obj2;
    throw std::exception();  // Exception thrown
    // Destructors called in reverse order: obj2, then obj1
}
```

## 🧱 RAII Pattern

### Resource Acquisition Is Initialization
```cpp
class FileHandler {
public:
    FileHandler(const std::string& filename) {
        file = fopen(filename.c_str(), "r");
        if (!file) throw std::runtime_error("Cannot open file");
    }
    
    ~FileHandler() {  // Automatic cleanup
        if (file) {
            fclose(file);
            std::cout << "File closed automatically" << std::endl;
        }
    }
    
private:
    FILE* file;
};

// Usage - guaranteed cleanup
{
    FileHandler handler("data.txt");
    // Use file...
}  // File automatically closed, even if exception occurs
```

**RAII Benefits:**
- **Automatic resource management**
- **Exception safety**
- **No resource leaks**
- **Deterministic cleanup**

## 🎭 Virtual Destructors

### Why Virtual Destructors Matter
```cpp
class Base {
public:
    virtual ~Base() {  // Virtual destructor
        std::cout << "Base destructor" << std::endl;
    }
};

class Derived : public Base {
private:
    int* data;
    
public:
    Derived() { data = new int[100]; }
    
    ~Derived() override {
        delete[] data;
        std::cout << "Derived destructor" << std::endl;
    }
};

// Proper cleanup with virtual destructor
Base* ptr = new Derived();
delete ptr;  // Both Derived and Base destructors called
```

### Without Virtual Destructor (Dangerous!)
```cpp
class Base {
public:
    ~Base() { }  // Non-virtual destructor
};

class Derived : public Base {
    ~Derived() { /* cleanup code */ }
};

Base* ptr = new Derived();
delete ptr;  // Only Base destructor called! Derived cleanup skipped!
```

**Rule:** Always make base class destructors virtual if the class is intended for inheritance.

## 🛡️ Exception Safety

### Destructors Should Not Throw
```cpp
class SafeClass {
public:
    ~SafeClass() noexcept {  // Mark as noexcept
        try {
            // Risky operation
            cleanup();
        } catch (...) {
            // Log error, but don't propagate
            std::cerr << "Cleanup failed" << std::endl;
        }
    }
    
private:
    void cleanup();
};
```

**Why destructors shouldn't throw:**
- Called during **stack unwinding**
- If destructor throws during stack unwinding → **std::terminate**
- **Undefined behavior** in many scenarios

### Exception-Safe Resource Management
```cpp
class ResourceManager {
public:
    ResourceManager(size_t size) : data(new int[size]) {}
    
    ~ResourceManager() {
        delete[] data;  // Simple operations that won't throw
    }
    
    // Rule of Three/Five for proper resource management
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
private:
    int* data;
};
```

## 🔧 Order of Destruction

### Local Objects
```cpp
void function() {
    Object obj1;
    Object obj2;
    Object obj3;
    // Destruction order: obj3, obj2, obj1 (reverse of construction)
}
```

### Inheritance Chain
```cpp
class Base {
public:
    ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Derived : public Base {
public:
    ~Derived() { std::cout << "Derived destructor" << std::endl; }
};

// Output when Derived object destroyed:
// "Derived destructor"
// "Base destructor"
```

### Member Objects
```cpp
class Member {
public:
    ~Member() { std::cout << "Member destructor" << std::endl; }
};

class Container {
public:
    ~Container() { std::cout << "Container destructor" << std::endl; }
    
private:
    Member m1, m2;  // Members destroyed in reverse order: m2, m1
};

// Output when Container destroyed:
// "Container destructor"
// "Member destructor" (m2)
// "Member destructor" (m1)
```

## 🎯 Best Practices

### ✅ Good Practices
```cpp
class GoodClass {
public:
    // Virtual destructor for base classes
    virtual ~GoodClass() noexcept = default;
    
    // Explicit resource management
    GoodClass() : resource(new Resource()) {}
    
    ~GoodClass() {
        delete resource;  // Clean, simple operations
    }
    
    // Follow Rule of Five
    GoodClass(const GoodClass&) = delete;
    GoodClass& operator=(const GoodClass&) = delete;
    GoodClass(GoodClass&&) noexcept = default;
    GoodClass& operator=(GoodClass&&) noexcept = default;
    
private:
    Resource* resource;
};
```

### ❌ Avoid
```cpp
class BadClass {
public:
    ~BadClass() {
        // DON'T: Throwing exceptions
        if (error) throw std::runtime_error("Error in destructor");
        
        // DON'T: Complex operations that might fail
        complexOperation();
        
        // DON'T: Calling virtual functions
        virtualFunction();
    }
    
    virtual void virtualFunction() {}
};
```

## 🚀 Modern C++ Alternatives

### Smart Pointers (Preferred)
```cpp
class Modern {
private:
    std::unique_ptr<int[]> data;  // Automatic cleanup
    
public:
    Modern(size_t size) : data(std::make_unique<int[]>(size)) {}
    
    // No custom destructor needed!
    // ~Modern() = default;  // Implicit, handles cleanup automatically
};
```

### RAII Containers
```cpp
class Container {
private:
    std::vector<int> data;      // Automatic cleanup
    std::string name;           // Automatic cleanup
    std::unique_ptr<File> file; // Automatic cleanup
    
public:
    // No destructor needed - all members clean themselves up!
};
```

## 📚 Summary

- **Destructors clean up** when objects are destroyed
- Use **RAII pattern** for automatic resource management
- **Virtual destructors** essential for proper inheritance cleanup
- **Never throw exceptions** from destructors
- **Modern C++** reduces need for custom destructors with smart pointers
- Follow **Rule of Three/Five** for classes managing resources
- **Prefer smart pointers** over raw pointers for automatic memory management
