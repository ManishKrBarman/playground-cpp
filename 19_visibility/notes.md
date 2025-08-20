## 👁️ Visibility in C++

## 🎯 What is Visibility?

Visibility (access control) determines **who can access** class members. C++ provides three access levels that control encapsulation - the principle of hiding internal implementation details.

```cpp
class Example {
private:    // Only this class can access
    int privateData;
    
protected:  // This class and derived classes can access
    int protectedData;
    
public:     // Everyone can access
    int publicData;
};
```

## 🔒 Access Levels

### Private Access
```cpp
class BankAccount {
private:
    double balance;        // Only BankAccount methods can access
    std::string pin;       // Hidden from outside world
    
    bool validatePin(const std::string& inputPin) {  // Private helper
        return pin == inputPin;
    }
    
public:
    // Controlled access through public interface
    double getBalance() const { return balance; }
    bool withdraw(double amount, const std::string& inputPin);
};

BankAccount account;
// account.balance = 1000;  // ERROR: private member
account.getBalance();       // OK: public interface
```

**Use private for:**
- **Internal implementation** details
- **Data that should not be modified** directly
- **Helper methods** not meant for public use
- **Maintaining class invariants**

### Protected Access
```cpp
class Vehicle {
protected:
    int speed;             // Accessible to derived classes
    std::string engine;    // Shared with inheritance hierarchy
    
    void startEngine() {   // Available to derived classes
        std::cout << "Engine started" << std::endl;
    }
    
public:
    void accelerate();
};

class Car : public Vehicle {
public:
    void turboBoost() {
        speed += 50;       // OK: can access protected member
        startEngine();     // OK: can access protected method
    }
};

Car myCar;
// myCar.speed = 100;     // ERROR: protected member not accessible outside
```

**Use protected for:**
- **Shared data/methods** in inheritance hierarchies
- **Implementation details** that derived classes need
- **Extension points** for customization

### Public Access
```cpp
class Calculator {
public:
    double add(double a, double b) { return a + b; }     // Interface method
    double result;                                       // Public data (usually avoid)
    
    void display() const {                              // Public service
        std::cout << "Result: " << result << std::endl;
    }
};

Calculator calc;
calc.result = calc.add(5, 3);  // OK: public access
calc.display();                 // OK: public method
```

**Use public for:**
- **Class interface** - methods clients should use
- **Constants** that are meant to be shared
- **Constructors and destructors**

## 🏗️ Struct vs Class Default Access

### Struct - Public by Default
```cpp
struct Point {
    double x, y;  // Public by default - no access specifier needed
    
    void display() {  // Public by default
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
    
private:
    int id;  // Must explicitly specify private
};
```

### Class - Private by Default
```cpp
class Point {
    double x, y;  // Private by default
    
    void display() { }  // Private by default
    
public:
    Point(double x, double y);  // Must explicitly specify public
    void show() const;
};
```

**Convention**: Use `struct` for simple data holders, `class` for complex objects with behavior.

## 🔗 Access Control with Inheritance

### Public Inheritance (Most Common)
```cpp
class Base {
public:    int publicMember;
protected: int protectedMember;  
private:   int privateMember;
};

class Derived : public Base {  // Public inheritance
    // publicMember    → public
    // protectedMember → protected
    // privateMember   → not accessible
};

Derived d;
d.publicMember = 10;  // OK: still public
```

### Protected Inheritance (Rare)
```cpp
class Derived : protected Base {  // Protected inheritance
    // publicMember    → protected
    // protectedMember → protected
    // privateMember   → not accessible
};

Derived d;
// d.publicMember = 10;  // ERROR: now protected
```

### Private Inheritance ("Implemented-in-terms-of")
```cpp
class Derived : private Base {  // Private inheritance
    // publicMember    → private
    // protectedMember → private  
    // privateMember   → not accessible
    
public:
    using Base::publicMember;  // Selectively make public again
};
```

### Inheritance Access Summary
| Base Access | Public Inheritance | Protected Inheritance | Private Inheritance |
|-------------|-------------------|----------------------|---------------------|
| public      | public            | protected            | private             |
| protected   | protected         | protected            | private             |
| private     | not accessible    | not accessible       | not accessible      |

## 👥 Friend Functions and Classes

### Friend Functions
```cpp
class Rectangle {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    // Friend function can access private members
    friend double calculateArea(const Rectangle& rect);
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect);
};

// Friend function implementation
double calculateArea(const Rectangle& rect) {
    return rect.width * rect.height;  // Can access private members
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rect) {
    os << "Rectangle(" << rect.width << "x" << rect.height << ")";
    return os;
}
```

### Friend Classes
```cpp
class Engine {
private:
    int horsepower;
    
public:
    friend class Car;  // Car can access all Engine members
};

class Car {
public:
    void tuneEngine(Engine& engine) {
        engine.horsepower += 50;  // Can access private member
    }
};
```

**Friend Guidelines:**
- **Use sparingly** - breaks encapsulation
- **Prefer public interfaces** when possible
- **Good for operators** and closely related classes
- **Friend relationship is not inherited**

## 🛡️ Encapsulation Best Practices

### Data Validation in Setters
```cpp
class Temperature {
private:
    double celsius;
    
public:
    Temperature(double c) : celsius(c) {
        if (c < -273.15) celsius = -273.15;  // Absolute zero minimum
    }
    
    void setCelsius(double c) {
        if (c >= -273.15) {  // Validation
            celsius = c;
        }
    }
    
    double getCelsius() const { return celsius; }
    double getFahrenheit() const { return celsius * 9.0/5.0 + 32.0; }
};
```

### Immutable Objects
```cpp
class ImmutablePoint {
private:
    const double x, y;  // Cannot be modified after construction
    
public:
    ImmutablePoint(double x, double y) : x(x), y(y) {}
    
    double getX() const { return x; }
    double getY() const { return y; }
    
    // Return new object instead of modifying this one
    ImmutablePoint move(double dx, double dy) const {
        return ImmutablePoint(x + dx, y + dy);
    }
};
```

### PIMPL Idiom (Pointer to Implementation)
```cpp
// Header file - interface exposed
class Widget {
private:
    class Impl;          // Forward declaration
    std::unique_ptr<Impl> pImpl;  // Pointer to implementation
    
public:
    Widget();
    ~Widget();
    void doSomething();
};

// Source file - implementation hidden
class Widget::Impl {
public:
    // All the complex implementation details
    void complexOperation() { /* ... */ }
    
private:
    // Private implementation data
    std::vector<int> data;
    std::map<std::string, int> cache;
};

void Widget::doSomething() {
    pImpl->complexOperation();
}
```

## 🎯 When to Use Each Access Level

### ✅ Use Private For:
```cpp
class GoodEncapsulation {
private:
    // Internal state
    std::vector<int> data;
    mutable std::mutex mtx;
    
    // Helper methods
    void validateInput(int value) const;
    void updateInternalState();
    
    // Implementation details
    static constexpr int MAX_SIZE = 1000;
};
```

### ✅ Use Protected For:
```cpp
class ExtensibleBase {
protected:
    // Data that derived classes need
    std::string configuration;
    
    // Customization points
    virtual void onDataChanged() { }
    
    // Shared utilities for inheritance hierarchy
    void logMessage(const std::string& msg) const;
};
```

### ✅ Use Public For:
```cpp
class WellDesigned {
public:
    // Constructor/destructor
    WellDesigned();
    ~WellDesigned();
    
    // Primary interface
    void performAction();
    bool isReady() const;
    
    // Configuration (with validation)
    void setConfig(const Config& config);
    Config getConfig() const;
};
```

## ❌ Common Visibility Mistakes

### Don't Make Everything Public
```cpp
// BAD: No encapsulation
class BadClass {
public:
    int internalCounter;     // Should be private
    std::vector<int> data;   // Direct access - no validation
    void helperMethod();     // Internal detail exposed
};
```

### Don't Make Getters/Setters for Everything
```cpp
// BAD: Pointless encapsulation
class Pointless {
private:
    int value;
    
public:
    int getValue() const { return value; }        // Just use public member
    void setValue(int v) { value = v; }           // No validation or logic
};
```

### Don't Use Protected for Data (Usually)
```cpp
// BAD: Protected data breaks encapsulation for derived classes
class BadBase {
protected:
    int count;  // Derived classes can break invariants
};

// GOOD: Protected methods, private data
class GoodBase {
private:
    int count;
    
protected:
    void incrementCount() { count++; }  // Controlled access
    int getCount() const { return count; }
};
```

## 📚 Summary

- **Private**: Internal implementation, data validation, helper methods
- **Protected**: Shared functionality in inheritance hierarchies
- **Public**: Class interface, constructors, main functionality
- **Struct defaults to public**, class defaults to private
- **Inheritance affects access** - public inheritance preserves access levels
- **Friends break encapsulation** - use judiciously
- **Good encapsulation** hides implementation details and maintains invariants
- **Validate data** in setters, expose read-only access through getters
