## 🎭 Virtual Functions in C++

## 🎯 What are Virtual Functions?

Virtual functions enable **runtime polymorphism** - the ability to call the correct function based on the actual object type, not the pointer/reference type. They are the foundation of object-oriented programming in C++.

```cpp
class Base {
public:
    virtual void func() { std::cout << "Base version" << std::endl; }
};

class Derived : public Base {
public:
    void func() override { std::cout << "Derived version" << std::endl; }  
};

Base* ptr = new Derived();
ptr->func();  // Calls Derived::func() - virtual dispatch
```

## 🔧 How Virtual Functions Work

### Virtual Function Table (vtable)
```cpp
// Each class with virtual functions has a vtable
class Animal {
public:
    virtual void sound() = 0;  // Entry 0 in vtable
    virtual void move() = 0;   // Entry 1 in vtable
    virtual ~Animal() = default; // Entry 2 in vtable
};

// Each object has a vptr pointing to its class's vtable
class Dog : public Animal {
    // Dog's vtable:
    // [0] -> Dog::sound
    // [1] -> Dog::move  
    // [2] -> Dog::~Dog
};
```

### Runtime Dispatch Process
1. **Compile time**: Function call becomes vtable lookup
2. **Runtime**: Follow vptr to vtable, jump to correct function
3. **Performance**: Small overhead (1-2 extra memory accesses)

## 🎭 Types of Virtual Functions

### Regular Virtual Functions
```cpp
class Base {
public:
    virtual void method() {  // Can be overridden
        std::cout << "Base implementation" << std::endl;
    }
};

class Derived : public Base {
public:
    void method() override {  // Override base implementation
        std::cout << "Derived implementation" << std::endl;
    }
};
```

### Pure Virtual Functions
```cpp
class AbstractBase {
public:
    virtual void pureVirtual() = 0;  // Pure virtual - no implementation
    
    virtual void mixedVirtual() {    // Can have both pure and regular
        std::cout << "Base implementation" << std::endl;
    }
};

// Must implement all pure virtual functions to instantiate
class Concrete : public AbstractBase {
public:
    void pureVirtual() override {
        std::cout << "Concrete implementation" << std::endl;
    }
};
```

### Virtual Destructors
```cpp
class Base {
public:
    virtual ~Base() {  // Essential for proper cleanup
        std::cout << "Base destructor" << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() override {
        std::cout << "Derived destructor" << std::endl;
    }
};

Base* ptr = new Derived();
delete ptr;  // Both destructors called correctly
```

## ⚡ Virtual vs Non-Virtual Functions

### Behavior Comparison
```cpp
class Base {
public:
    virtual void virtualFunc() { std::cout << "Base virtual" << std::endl; }
    void nonVirtualFunc() { std::cout << "Base non-virtual" << std::endl; }
};

class Derived : public Base {
public:
    void virtualFunc() override { std::cout << "Derived virtual" << std::endl; }
    void nonVirtualFunc() { std::cout << "Derived non-virtual" << std::endl; }
};

Base* ptr = new Derived();
ptr->virtualFunc();    // Output: "Derived virtual" - dynamic dispatch
ptr->nonVirtualFunc(); // Output: "Base non-virtual" - static dispatch
```

### Performance Characteristics
| Aspect | Virtual Functions | Non-Virtual Functions |
|--------|------------------|----------------------|
| Binding time | Runtime | Compile time |
| Performance | Small overhead | No overhead |
| Polymorphism | ✅ Yes | ❌ No |
| Memory usage | vtable + vptr | None |
| Inlining | Limited | Full inlining |

## 🎯 The override Keyword (C++11)

### Why Use override?
```cpp
class Base {
public:
    virtual void func(int x) const = 0;
};

class Derived : public Base {
public:
    // Without override - silent error!
    void func(int x) { }  // Missing 'const' - doesn't override!
    
    // With override - compile error caught
    void func(int x) override { }  // ERROR: signature mismatch
    
    // Correct version
    void func(int x) const override { }  // ✅ Properly overrides
};
```

### Benefits of override
- **Catches typos** in function signatures
- **Documents intent** clearly
- **Compiler verification** that override is valid
- **Safer refactoring** when base class changes

## 🚫 Final Functions (C++11)

### Preventing Further Override
```cpp
class Base {
public:
    virtual void method() = 0;
};

class Middle : public Base {
public:
    void method() final override {  // Cannot be overridden further
        std::cout << "Final implementation" << std::endl;
    }
};

class End : public Middle {
public:
    // void method() override { }  // ERROR: Cannot override final function
};
```

## 🧪 Advanced Virtual Function Concepts

### Virtual Function Access Levels
```cpp
class Base {
public:
    virtual void publicVirtual() = 0;
};

class Derived : public Base {
private:
    // Can make public virtual function private!
    void publicVirtual() override { }  // Still overrides, but access changes
};

Base* ptr = new Derived();
ptr->publicVirtual();  // Calls private Derived version through public interface
```

### Covariant Return Types
```cpp
class Base {
public:
    virtual Base* clone() const {
        return new Base(*this);
    }
};

class Derived : public Base {
public:
    Derived* clone() const override {  // Covariant return type
        return new Derived(*this);
    }
};
```

### Virtual Functions in Constructors/Destructors
```cpp
class Dangerous {
public:
    Dangerous() {
        init();  // Calls Base::init, not derived version!
    }
    
    virtual ~Dangerous() {
        cleanup();  // Calls Base::cleanup during destruction
    }
    
    virtual void init() { std::cout << "Base init" << std::endl; }
    virtual void cleanup() { std::cout << "Base cleanup" << std::endl; }
};

// ⚠️ Virtual function calls in constructors/destructors don't use derived versions
```

## 🎯 When to Use Virtual Functions

### ✅ Use Virtual Functions When:
- You need **runtime polymorphism**
- **"Is-a" relationships** exist
- **Different behavior** for different derived classes
- **Interface consistency** across hierarchy

### ❌ Don't Use Virtual Functions When:
- **Performance is critical** and polymorphism unnecessary
- **No inheritance** is planned
- **Interface won't change** across derived classes
- **Template polymorphism** is sufficient

## 🚀 Alternatives to Virtual Functions

### Template-Based Polymorphism
```cpp
// Compile-time polymorphism - no virtual function overhead
template<typename T>
void processObject(const T& obj) {
    obj.doSomething();  // Resolved at compile time
}
```

### std::variant (C++17)
```cpp
#include <variant>

using Shape = std::variant<Circle, Rectangle, Triangle>;

void processShape(const Shape& shape) {
    std::visit([](const auto& s) { s.display(); }, shape);
}
```

### Function Pointers
```cpp
struct Interface {
    void (*display)(void* obj);
    double (*area)(void* obj);
};
```

## 🎯 Best Practices

### ✅ Good Practices
```cpp
class Good {
public:
    // Always virtual destructor for base classes
    virtual ~Good() = default;
    
    // Use pure virtual for interface contracts
    virtual void interface() = 0;
    
    // Use override keyword
    void interface() override final;
    
    // Document virtual function purpose
    virtual void process() {
        // Default implementation
    }
};
```

### ❌ Common Mistakes
```cpp
class Bad {
public:
    // Missing virtual destructor
    ~Bad() { }  // Dangerous for inheritance
    
    // Calling virtual functions in constructor
    Bad() { virtualFunc(); }  // Won't call derived version
    
    // Missing override keyword
    virtual void func();
};

class BadDerived : public Bad {
public:
    void func();  // Is this an override? Unclear without 'override'
};
```

## 📊 Performance Considerations

### Virtual Function Costs
```cpp
// Virtual function call
ptr->virtualFunc();  // ~2-3 CPU cycles overhead
    // 1. Load vptr from object
    // 2. Index into vtable  
    // 3. Jump to function

// Non-virtual function call  
ptr->nonVirtualFunc();  // Direct jump - no overhead
```

### Optimization Tips
- **Profile first** - virtual function overhead often negligible
- **Consider templates** for compile-time polymorphism
- **Use final** to help compiler optimize
- **Avoid virtual functions in tight loops** if performance critical

## 📚 Summary

- **Virtual functions** enable runtime polymorphism through vtable mechanism
- **Pure virtual functions** create abstract interfaces
- **Virtual destructors** essential for proper inheritance cleanup
- **override keyword** prevents common override mistakes
- **Small performance cost** but enables powerful design patterns
- **Choose wisely** between runtime and compile-time polymorphism based on needs
