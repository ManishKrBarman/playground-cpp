## 📦 Structs in C++

## 🎯 What is a Struct?

In C++, a struct is **almost identical to a class** with one key difference:
- **Struct**: Members are `public` by default
- **Class**: Members are `private` by default

```cpp
struct Point {
    double x, y;  // Public by default - no access specifier needed
};

class Point {
    double x, y;  // Private by default - would need 'public:'
};
```

## 🔧 Basic Struct Usage

### Simple Data Container
```cpp
struct Student {
    std::string name;
    int age;
    double gpa;
};

// Creating and using
Student s1;                           // Default initialization
Student s2{"Alice", 20, 3.8};        // Aggregate initialization
Student s3 = {"Bob", 22, 3.5};       // Copy initialization

s1.name = "Charlie";                  // Direct member access
std::cout << s2.name << std::endl;   // Direct member access
```

### Struct with Constructor
```cpp
struct Rectangle {
    double width, height;
    
    // Constructor
    Rectangle(double w, double h) : width(w), height(h) {}
    
    // Default constructor
    Rectangle() : width(0), height(0) {}
    
    // Member function
    double area() const {
        return width * height;
    }
};
```

## 🏗️ Advanced Struct Features

### Mixed Access Levels
```cpp
struct Employee {
    std::string name;      // Public by default
    int id;
    
private:
    double salary;         // Private member
    
public:
    Employee(const std::string& n, int i, double s) 
        : name(n), id(i), salary(s) {}
    
    double getSalary() const { return salary; }
    void setSalary(double s) { if (s > 0) salary = s; }
};
```

### Nested Structs
```cpp
struct Address {
    std::string street;
    std::string city;
    int zipCode;
};

struct Person {
    std::string name;
    Address address;     // Nested struct
    
    void display() const {
        std::cout << name << " lives at " << address.street 
                  << ", " << address.city << std::endl;
    }
};
```

## 📊 Plain Old Data (POD) Structs

### POD Characteristics
A struct is POD if it:
- Has no user-defined constructors
- Has no virtual functions
- Has no virtual base classes
- All members are POD types

```cpp
// POD struct
struct Color {
    unsigned char r, g, b, a;
};

// Can be initialized with braces
Color red = {255, 0, 0, 255};
Color blue{0, 0, 255, 255};    // C++11 uniform initialization

// Can be memcpy'd safely
Color colors[10];
memset(colors, 0, sizeof(colors));  // Safe for POD types
```

### Aggregate Initialization
```cpp
struct Point3D {
    double x, y, z;
};

// Different initialization methods
Point3D p1{1.0, 2.0, 3.0};        // Uniform initialization
Point3D p2 = {1.0, 2.0, 3.0};     // Aggregate initialization  
Point3D p3{};                      // Zero initialization
```

## 💾 Memory Layout

### Struct Memory Alignment
```cpp
struct Example {
    char a;      // 1 byte
    int b;       // 4 bytes
    double c;    // 8 bytes
};

// Memory layout (with padding):
// [a][___][bbbb][cccccccc]
//  1   3    4       8     = 16 bytes total

sizeof(Example);  // Usually 16, not 13 (due to alignment)
```

### Packed Structs
```cpp
#pragma pack(1)    // Remove padding
struct Packed {
    char a;        // 1 byte
    int b;         // 4 bytes  
    double c;      // 8 bytes
};                 // Total: 13 bytes (no padding)
#pragma pack()     // Restore default packing
```

**Warning**: Packed structs may have **performance penalties** due to unaligned memory access.

## 🚀 Modern C++ Struct Features

### Designated Initializers (C++20)
```cpp
struct Config {
    int width = 800;
    int height = 600;
    bool fullscreen = false;
    std::string title = "Default";
};

// C++20 designated initializers
Config cfg = {
    .width = 1920,
    .height = 1080,
    .fullscreen = true,
    .title = "My Game"
};
```

### Structured Bindings (C++17)
```cpp
struct Point {
    double x, y;
};

Point getPoint() {
    return {3.0, 4.0};
}

// Structured binding
auto [x, y] = getPoint();
std::cout << "x: " << x << ", y: " << y << std::endl;
```

## 🎯 Struct vs Class Guidelines

### When to Use Struct
```cpp
// ✅ Simple data containers
struct Color { unsigned char r, g, b, a; };

// ✅ Mathematical types
struct Vector3 { double x, y, z; };

// ✅ Configuration data
struct Settings {
    int width, height;
    bool fullscreen;
    std::string theme;
};

// ✅ Return multiple values
struct ParseResult {
    bool success;
    std::string value;
    std::string error;
};
```

### When to Use Class
```cpp
// ✅ Complex objects with behavior
class BankAccount {
private:
    double balance;  // Data should be private
public:
    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;
};

// ✅ Objects requiring resource management
class FileHandler {
private:
    FILE* file;
public:
    FileHandler(const char* filename);
    ~FileHandler();
    // RAII pattern
};
```

## 📝 Struct Best Practices

### 1. Use for Simple Data
```cpp
// ✅ Good - simple data structure
struct Employee {
    std::string name;
    int id;
    std::string department;
};

// ❌ Overkill for simple data
class Employee {
private:
    std::string name;
    int id; 
    std::string department;
public:
    // Lots of getters/setters for simple data
};
```

### 2. Provide Constructors for Complex Initialization
```cpp
struct Rectangle {
    double width, height;
    
    Rectangle(double w, double h) : width(w), height(h) {
        if (w < 0 || h < 0) {
            throw std::invalid_argument("Negative dimensions");
        }
    }
};
```

### 3. Use Const Member Functions
```cpp
struct Circle {
    double radius;
    
    double area() const {        // ✅ Const member function
        return 3.14159 * radius * radius;
    }
    
    double circumference() const {
        return 2 * 3.14159 * radius;
    }
};
```

### 4. Consider Default Member Initializers (C++11)
```cpp
struct Config {
    int width = 1920;        // Default value
    int height = 1080;
    bool fullscreen = false;
    
    Config() = default;      // Use compiler-generated constructor
    Config(int w, int h) : width(w), height(h) {}  // Custom constructor
};
```

## 🔍 Common Use Cases

### Function Return Values
```cpp
struct DivisionResult {
    double quotient;
    double remainder;
    bool valid;
};

DivisionResult divide(double a, double b) {
    if (b == 0) {
        return {0.0, 0.0, false};
    }
    return {a / b, std::fmod(a, b), true};
}

auto result = divide(10, 3);
if (result.valid) {
    std::cout << "Quotient: " << result.quotient << std::endl;
}
```

### Data Transfer Objects (DTOs)
```cpp
struct UserData {
    std::string username;
    std::string email;
    int age;
    bool isActive;
    
    // Serialization method
    std::string toJson() const {
        // Convert to JSON string
    }
};
```

### Configuration Structs
```cpp
struct DatabaseConfig {
    std::string host = "localhost";
    int port = 5432;
    std::string database;
    std::string username;
    std::string password;
    int maxConnections = 10;
};
```

### Coordinate Systems
```cpp
struct Point2D { double x, y; };
struct Point3D { double x, y, z; };

struct Transform {
    Point3D position;
    Point3D rotation;
    Point3D scale{1.0, 1.0, 1.0};  // Default scale
};
```

## 💡 Performance Considerations

### Struct Copying
```cpp
struct LargeStruct {
    double data[1000];  // 8KB of data
};

// ❌ Expensive copy
void processStruct(LargeStruct s) {
    // Entire struct copied
}

// ✅ Pass by const reference
void processStruct(const LargeStruct& s) {
    // No copying - reference only
}
```

### Memory Layout Optimization
```cpp
// ❌ Poor layout (lots of padding)
struct BadLayout {
    char a;     // 1 byte + 7 padding
    double b;   // 8 bytes
    char c;     // 1 byte + 7 padding  
    double d;   // 8 bytes
};              // Total: 32 bytes

// ✅ Better layout (less padding)
struct GoodLayout {
    double b;   // 8 bytes
    double d;   // 8 bytes
    char a;     // 1 byte
    char c;     // 1 byte + 6 padding
};              // Total: 24 bytes
```

---
<div align='center'>
If I missed anything, feel free to reach me
</div>