## 🏗️ Classes in C++

## 🎯 What is a Class?

A class is a **user-defined data type** that groups:
- **Data members** (attributes/variables)
- **Member functions** (methods/behaviors)
- **Access control** (public, private, protected)

Classes are the foundation of **Object-Oriented Programming (OOP)**.

```cpp
class Rectangle {
private:
    double width, height;  // Data members

public:
    Rectangle(double w, double h) : width(w), height(h) {}  // Constructor
    double getArea() { return width * height; }             // Member function
};
```

## 🔐 Access Specifiers

### Private
```cpp
class MyClass {
private:
    int privateVar;        // Only accessible within the class
    void privateFunction() { /* Only class can call this */ }
};
```

### Public
```cpp
class MyClass {
public:
    int publicVar;         // Accessible from anywhere
    void publicFunction() { /* Anyone can call this */ }
};
```

### Protected
```cpp
class MyClass {
protected:
    int protectedVar;      // Accessible by class and derived classes
};
```

**Default access**: `private` for classes, `public` for structs

## 🏗️ Constructors

### Default Constructor
```cpp
class Rectangle {
public:
    Rectangle() : width(0), height(0) {  // Member initializer list
        std::cout << "Default constructor called" << std::endl;
    }
private:
    double width, height;
};
```

### Parameterized Constructor
```cpp
class Rectangle {
public:
    Rectangle(double w, double h) : width(w), height(h) {
        // Constructor body (optional)
    }
private:
    double width, height;
};
```

### Copy Constructor
```cpp
class Rectangle {
public:
    // Copy constructor
    Rectangle(const Rectangle& other) : width(other.width), height(other.height) {
        std::cout << "Copy constructor called" << std::endl;
    }
private:
    double width, height;
};

Rectangle rect1(5, 3);
Rectangle rect2 = rect1;  // Copy constructor called
Rectangle rect3(rect1);   // Copy constructor called
```

### Constructor Delegation (C++11)
```cpp
class Rectangle {
public:
    Rectangle() : Rectangle(0, 0) {  // Delegates to parameterized constructor
        // Additional initialization if needed
    }
    
    Rectangle(double w, double h) : width(w), height(h) {
        // Main initialization logic
    }
private:
    double width, height;
};
```

## 💀 Destructor

**Called when object is destroyed** (goes out of scope or explicitly deleted):

```cpp
class Rectangle {
public:
    ~Rectangle() {  // Destructor
        std::cout << "Rectangle destroyed" << std::endl;
        // Cleanup resources (close files, free memory, etc.)
    }
};

{
    Rectangle rect(5, 3);
}  // Destructor called here automatically
```

### RAII (Resource Acquisition Is Initialization)
```cpp
class FileHandler {
private:
    FILE* file;
    
public:
    FileHandler(const char* filename) {
        file = fopen(filename, "r");  // Acquire resource in constructor
    }
    
    ~FileHandler() {
        if (file) {
            fclose(file);  // Release resource in destructor
        }
    }
};
```

## 🔧 Member Functions

### Const Member Functions
```cpp
class Rectangle {
public:
    double getArea() const {  // Promise not to modify object
        return width * height;
    }
    
    void setWidth(double w) {  // Can modify object
        width = w;
    }
    
private:
    double width, height;
};

const Rectangle rect(5, 3);
rect.getArea();    // ✅ OK - const function
// rect.setWidth(4);  // ❌ Error - non-const function on const object
```

### Static Member Functions
```cpp
class MathUtils {
public:
    static double pi() {      // Static function
        return 3.14159;
    }
    
    static int count;         // Static data member
};

int MathUtils::count = 0;     // Definition outside class

// Called without object
double piValue = MathUtils::pi();
```

## 💾 Memory Layout

### Object Memory Layout
```cpp
class Example {
    int a;        // 4 bytes
    double b;     // 8 bytes  
    char c;       // 1 byte
    // Padding may be added for alignment
};

sizeof(Example);  // Likely 24 bytes (due to padding)
```

### Memory Layout Visualization
```
Object in Memory:
┌─────────┬─────────────────┬─────┬───────┐
│ int a   │    double b     │char │ pad   │
│ 4 bytes │    8 bytes      │ 1   │ 3     │
└─────────┴─────────────────┴─────┴───────┘
Total: 16 bytes (due to alignment)
```

### Stack vs Heap Objects
```cpp
// Stack object
Rectangle stackRect(5, 3);  // Created on stack, automatically destroyed

// Heap object
Rectangle* heapRect = new Rectangle(5, 3);  // Created on heap
delete heapRect;  // Must manually destroy
```

## 🎯 Object Lifecycle

### Creation Order
1. **Memory allocated** (stack or heap)
2. **Base class constructors** called (if inheritance)
3. **Member objects constructed** (in declaration order)
4. **Constructor body** executed

### Destruction Order
1. **Destructor body** executed
2. **Member objects destroyed** (reverse declaration order)
3. **Base class destructors** called (if inheritance)
4. **Memory deallocated**

```cpp
class Member {
public:
    Member() { std::cout << "Member constructed\n"; }
    ~Member() { std::cout << "Member destroyed\n"; }
};

class Owner {
    Member m1, m2;  // Constructed in order: m1, then m2
public:
    Owner() { std::cout << "Owner constructed\n"; }
    ~Owner() { std::cout << "Owner destroyed\n"; }
};  // Destroyed in reverse: m2, then m1

Owner obj;
// Output:
// Member constructed (m1)
// Member constructed (m2)  
// Owner constructed
// Owner destroyed
// Member destroyed (m2)
// Member destroyed (m1)
```

## 🚀 Advanced Class Features

### Friend Functions
```cpp
class Rectangle {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    friend double calculateArea(const Rectangle& rect);  // Friend declaration
};

// Friend function can access private members
double calculateArea(const Rectangle& rect) {
    return rect.width * rect.height;  // Direct access to private members
}
```

### Operator Overloading
```cpp
class Vector2D {
public:
    double x, y;
    
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}
    
    // Overload + operator
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    // Overload << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

Vector2D v1(1, 2);
Vector2D v2(3, 4);
Vector2D result = v1 + v2;  // Uses overloaded + operator
std::cout << result;        // Uses overloaded << operator
```

### Move Semantics (C++11)
```cpp
class Resource {
private:
    int* data;
    size_t size;
    
public:
    // Move constructor
    Resource(Resource&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;  // Leave other in valid state
        other.size = 0;
    }
    
    // Move assignment operator
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;          // Clean up current resource
            data = other.data;      // Take ownership
            size = other.size;
            other.data = nullptr;   // Leave other in valid state
            other.size = 0;
        }
        return *this;
    }
};
```

## 🎯 Best Practices

### 1. Encapsulation
```cpp
class BankAccount {
private:
    double balance;  // Hide implementation details
    
public:
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    double getBalance() const { return balance; }
    // Don't provide direct access to balance
};
```

### 2. Use Initializer Lists
```cpp
class Example {
    const int constantMember;
    int& referenceMember;
    
public:
    // ✅ Use initializer list for const and reference members
    Example(int value, int& ref) 
        : constantMember(value), referenceMember(ref) {}
        
    // ❌ This won't work - const/reference must be initialized
    // Example(int value, int& ref) {
    //     constantMember = value;  // Error!
    //     referenceMember = ref;   // Error!
    // }
};
```

### 3. Rule of Three/Five
If you need one, you probably need all:

```cpp
class Resource {
public:
    // Destructor
    ~Resource() { delete[] data; }
    
    // Copy constructor
    Resource(const Resource& other) {
        size = other.size;
        data = new int[size];
        std::copy(other.data, other.data + size, data);
    }
    
    // Copy assignment operator
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }
    
    // C++11: Move constructor and move assignment operator
    
private:
    int* data;
    size_t size;
};
```

### 4. Prefer const Member Functions
```cpp
class Rectangle {
public:
    double getArea() const {  // ✅ Const - can be called on const objects
        return width * height;
    }
    
    void display() const {    // ✅ Const - doesn't modify object
        std::cout << "Area: " << getArea() << std::endl;
    }
};
```

## 🔍 Common Pitfalls

### 1. Uninitialized Members
```cpp
class Example {
    int value;  // ❌ Uninitialized - contains garbage
    
public:
    Example() {
        // ❌ Forgot to initialize value
    }
};

// ✅ Fix: Always initialize in constructor
class Example {
    int value;
    
public:
    Example() : value(0) {}  // ✅ Initialized
};
```

### 2. Shallow Copy Problem
```cpp
class Resource {
    int* data;
    
public:
    Resource(int size) : data(new int[size]) {}
    
    // ❌ Default copy constructor does shallow copy
    // Both objects will point to same memory!
    
    ~Resource() { delete[] data; }  // ❌ Double deletion!
};
```

### 3. Missing Virtual Destructor
```cpp
class Base {
public:
    ~Base() { /* cleanup */ }  // ❌ Should be virtual for inheritance
};

class Derived : public Base {
public:
    ~Derived() { /* cleanup */ }
};

Base* ptr = new Derived();
delete ptr;  // ❌ Only Base destructor called!
```

---
<div align='center'>
If I missed anything, feel free to reach me
</div>