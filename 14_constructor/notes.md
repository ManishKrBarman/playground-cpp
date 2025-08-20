## 🏗️ Constructors in C++

## 🎯 What are Constructors?

Constructors are **special member functions** that initialize objects when they are created. They:
- Have the **same name** as the class
- **No return type** (not even void)
- **Automatically called** during object creation
- Can be **overloaded** with different parameters

```cpp
class Student {
public:
    Student() { }                    // Default constructor
    Student(string name) { }         // Parameterized constructor
};
```

## 🔧 Types of Constructors

### Default Constructor
```cpp
class Point {
public:
    Point() : x(0), y(0) {  // Member initializer list
        std::cout << "Default constructor called" << std::endl;
    }
    
private:
    double x, y;
};

Point p;  // Calls default constructor
```

**Key points:**
- **No parameters** or **all parameters have defaults**
- **Compiler generates** one if you don't provide any constructor
- **Not generated** if you define any constructor

### Parameterized Constructor
```cpp
class Rectangle {
public:
    Rectangle(double w, double h) : width(w), height(h) {
        std::cout << "Rectangle created: " << w << "x" << h << std::endl;
    }
    
private:
    double width, height;
};

Rectangle r(5.0, 3.0);  // Direct initialization
Rectangle r2{4.0, 2.0}; // Uniform initialization (C++11)
```

### Copy Constructor
```cpp
class MyClass {
public:
    MyClass(const MyClass& other) : data(other.data) {
        std::cout << "Copy constructor called" << std::endl;
    }
    
private:
    int data;
};

MyClass obj1;
MyClass obj2 = obj1;  // Copy constructor called
MyClass obj3(obj1);   // Copy constructor called
```

**When called:**
- Object **initialization** from another object
- **Pass by value** to functions
- **Return by value** from functions

### Move Constructor (C++11)
```cpp
class MyClass {
public:
    MyClass(MyClass&& other) noexcept : data(std::move(other.data)) {
        std::cout << "Move constructor called" << std::endl;
        other.data = nullptr;  // Leave other in valid state
    }
    
private:
    std::string* data;
};
```

**Key benefits:**
- **Avoids expensive copies** for temporary objects
- **Transfers ownership** of resources
- **Better performance** with containers and algorithms

## 🎯 Member Initialization List

### Syntax and Benefits
```cpp
class Student {
public:
    // Member initialization list (preferred)
    Student(string n, int a) : name(n), age(a), id(generateId()) {
        // Constructor body - for complex initialization
    }
    
    // vs Assignment in constructor body (less efficient)
    Student(string n, int a) {
        name = n;  // Assignment, not initialization
        age = a;
    }
    
private:
    const int id;     // MUST be initialized in member init list
    string name;
    int age;
};
```

**When required:**
- **const members**
- **Reference members** 
- **Members without default constructors**
- **Base class constructors**

### Initialization Order
```cpp
class Demo {
private:
    int a, b, c;  // Initialization order follows DECLARATION order
    
public:
    Demo(int x) : c(x), a(c), b(a) {  // Dangerous! a uses uninitialized c
        // Members initialized in order: a, b, c (not c, a, b)
    }
};
```

## 🔧 Advanced Constructor Features

### Constructor Delegation (C++11)
```cpp
class Point {
public:
    Point() : Point(0.0, 0.0) {         // Delegates to two-param constructor
        std::cout << "Default constructor" << std::endl;
    }
    
    Point(double val) : Point(val, val) { // Delegates to two-param constructor
        std::cout << "Single value constructor" << std::endl;
    }
    
    Point(double x, double y) : x_(x), y_(y) {  // Target constructor
        std::cout << "Two-parameter constructor" << std::endl;
    }
    
private:
    double x_, y_;
};
```

### Explicit Constructors
```cpp
class Temperature {
public:
    explicit Temperature(double celsius) : temp_(celsius) {}
    
private:
    double temp_;
};

Temperature t1(25.0);      // OK: Direct initialization
// Temperature t2 = 30.0;  // ERROR: Implicit conversion prevented
```

**When to use:**
- **Single-parameter constructors** to prevent implicit conversions
- **Clearer intent** and fewer bugs

### Deleted Constructors (C++11)
```cpp
class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;  // No copy constructor
    NonCopyable& operator=(const NonCopyable&) = delete;  // No copy assignment
};
```

### Default and Explicitly-Defaulted
```cpp
class MyClass {
public:
    MyClass() = default;              // Use compiler-generated default
    MyClass(int x) : value(x) {}      // Custom constructor
    
private:
    int value = 42;  // Default member initialization (C++11)
};
```

## 🎯 Best Practices

### ✅ Good Practices
```cpp
class Good {
public:
    // Use member initializer lists
    Good(string n, int a) : name(n), age(a) {}
    
    // Make single-param constructors explicit
    explicit Good(string n) : name(n), age(0) {}
    
    // Use noexcept for move constructors
    Good(Good&& other) noexcept : name(std::move(other.name)) {}
    
private:
    string name;
    int age;
};
```

### ❌ Avoid
```cpp
class Bad {
public:
    // Don't use assignment in constructor body when initialization works
    Bad(string n, int a) {
        name = n;  // Assignment, not initialization
        age = a;
    }
    
    // Don't forget explicit for single-param constructors
    Bad(string n) : name(n) {}  // Allows implicit conversions
};
```

## 🧪 RAII Pattern

### Resource Acquisition Is Initialization
```cpp
class FileHandler {
public:
    FileHandler(const string& filename) : file_(filename) {
        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open file");
        }
    }
    
    ~FileHandler() {  // Automatic cleanup
        if (file_.is_open()) {
            file_.close();
        }
    }
    
private:
    std::ifstream file_;
};

// Usage - automatic resource management
{
    FileHandler handler("data.txt");
    // Use file...
}  // Destructor automatically closes file
```

## 📚 Summary

- **Default constructor** for basic initialization
- **Parameterized constructor** for custom initialization  
- **Copy constructor** for object copying
- **Move constructor** for efficient transfers (C++11)
- **Use member initializer lists** for efficiency
- **Make single-param constructors explicit** to prevent implicit conversions
- **Follow RAII pattern** for resource management
