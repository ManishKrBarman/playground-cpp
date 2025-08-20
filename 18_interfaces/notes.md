## 🔌 Interfaces in C++

## 🎯 What are Interfaces?

C++ doesn't have a dedicated `interface` keyword like Java or C#, but achieves interfaces through **abstract classes with only pure virtual functions**. An interface defines a contract that implementing classes must follow.

```cpp
class Drawable {  // Interface - all functions pure virtual
public:
    virtual ~Drawable() = default;
    virtual void draw() const = 0;           // Pure virtual
    virtual void setColor(const std::string& color) = 0;  // Pure virtual
};
```

## 🏗️ Creating Interfaces

### Pure Interface (Recommended)
```cpp
class Serializable {
public:
    virtual ~Serializable() = default;  // Always virtual destructor
    
    // Only pure virtual functions
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string& data) = 0;
};
```

### Mixed Interface (Less Common)
```cpp
class Logger {
public:
    virtual ~Logger() = default;
    
    virtual void log(const std::string& msg) = 0;  // Pure virtual
    
    virtual void setLevel(int level) {              // Default implementation
        logLevel = level;
    }
    
protected:
    int logLevel = 0;
};
```

**Best Practice**: Use pure interfaces (all functions pure virtual) for cleaner contracts.

## 🔗 Implementing Interfaces

### Single Interface Implementation
```cpp
class FileLogger : public Logger {
public:
    void log(const std::string& msg) override {
        std::cout << "[FILE] " << msg << std::endl;
    }
};
```

### Multiple Interface Implementation
```cpp
class Document : public Drawable, public Serializable, public Printable {
public:
    // Must implement all pure virtual functions from all interfaces
    void draw() const override { /* implementation */ }
    std::string serialize() const override { /* implementation */ }  
    void print() const override { /* implementation */ }
};
```

## 🎭 Polymorphism with Interfaces

### Interface-Based Polymorphism
```cpp
void processDrawable(Drawable& obj) {
    obj.setColor("Blue");
    obj.draw();  // Calls appropriate implementation
}

Rectangle rect;
Circle circle; 
Triangle triangle;

processDrawable(rect);     // Works if Rectangle implements Drawable
processDrawable(circle);   // Works if Circle implements Drawable
processDrawable(triangle); // Works if Triangle implements Drawable
```

### Polymorphic Collections
```cpp
std::vector<std::unique_ptr<Drawable>> shapes;
shapes.push_back(std::make_unique<Rectangle>());
shapes.push_back(std::make_unique<Circle>());

for (const auto& shape : shapes) {
    shape->draw();  // Polymorphic call
}
```

## 🔄 Interface Casting

### Dynamic Casting Between Interfaces
```cpp
void processObject(Drawable* drawable) {
    drawable->draw();
    
    // Try to cast to other interfaces
    if (auto* resizable = dynamic_cast<Resizable*>(drawable)) {
        resizable->resize(1.5);
    }
    
    if (auto* serializable = dynamic_cast<Serializable*>(drawable)) {
        std::string data = serializable->serialize();
    }
}
```

### Interface Detection
```cpp
template<typename T>
void processIfDrawable(T& obj) {
    if constexpr (std::is_base_of_v<Drawable, T>) {
        obj.draw();
    }
}
```

## 🧩 Interface Segregation Principle

### Problem: Fat Interfaces
```cpp
// BAD: Fat interface forces unnecessary implementations
class AllInOnePrinter {
public:
    virtual void print(const std::string& doc) = 0;
    virtual void scan(const std::string& doc) = 0;
    virtual void fax(const std::string& doc) = 0;
    virtual void email(const std::string& doc) = 0;
};

class SimplePrinter : public AllInOnePrinter {
public:
    void print(const std::string& doc) override { /* OK */ }
    void scan(const std::string& doc) override { /* Forced to implement */ }
    void fax(const std::string& doc) override { /* Forced to implement */ }  
    void email(const std::string& doc) override { /* Forced to implement */ }
};
```

### Solution: Segregated Interfaces
```cpp
// GOOD: Segregated interfaces
class Printer {
public:
    virtual ~Printer() = default;
    virtual void print(const std::string& doc) = 0;
};

class Scanner {
public:
    virtual ~Scanner() = default;
    virtual void scan(const std::string& doc) = 0;
};

class FaxMachine {
public:
    virtual ~FaxMachine() = default;
    virtual void fax(const std::string& doc) = 0;
};

// Classes implement only what they need
class SimplePrinter : public Printer {
public:
    void print(const std::string& doc) override { /* Only this */ }
};

class MultiFunctionDevice : public Printer, public Scanner, public FaxMachine {
public:
    void print(const std::string& doc) override { /* implementation */ }
    void scan(const std::string& doc) override { /* implementation */ }
    void fax(const std::string& doc) override { /* implementation */ }
};
```

## 🎯 Dependency Inversion Principle

### High-Level Modules Depend on Abstractions
```cpp
// BAD: Depends on concrete class
class OrderProcessor {
    MySQLDatabase database;  // Tight coupling
    
public:
    void processOrder(const Order& order) {
        database.save(order);  // Depends on MySQL specifically
    }
};

// GOOD: Depends on interface
class OrderProcessor {
    Database& database;  // Depends on abstraction
    
public:
    OrderProcessor(Database& db) : database(db) {}
    
    void processOrder(const Order& order) {
        database.save(order);  // Works with any Database implementation
    }
};
```

## 🔧 Common Interface Patterns

### Strategy Pattern
```cpp
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<int>& data) = 0;
};

class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        // QuickSort implementation
    }
};

class MergeSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        // MergeSort implementation  
    }
};

class Sorter {
    SortStrategy& strategy;
public:
    Sorter(SortStrategy& s) : strategy(s) {}
    void sortData(std::vector<int>& data) {
        strategy.sort(data);
    }
};
```

### Observer Pattern
```cpp
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

class Subject {
    std::vector<Observer*> observers;
    
public:
    void subscribe(Observer* observer) {
        observers.push_back(observer);
    }
    
    void notify(const std::string& message) {
        for (auto* observer : observers) {
            observer->update(message);
        }
    }
};
```

### Factory Pattern
```cpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class ShapeFactory {
public:
    virtual ~ShapeFactory() = default;
    virtual std::unique_ptr<Shape> createShape() = 0;
};

class CircleFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() override {
        return std::make_unique<Circle>();
    }
};
```

## 🎯 Best Practices

### ✅ Interface Design Guidelines
```cpp
class GoodInterface {
public:
    // Always virtual destructor
    virtual ~GoodInterface() = default;
    
    // Keep interfaces small and focused
    virtual void singleResponsibility() = 0;
    
    // Use const correctness
    virtual std::string getData() const = 0;
    
    // Clear, descriptive names
    virtual bool isValid() const = 0;
    
    // Document preconditions/postconditions
    virtual void process() = 0;  // Processes data, throws on error
};
```

### ❌ Interface Anti-Patterns
```cpp
class BadInterface {
public:
    // Missing virtual destructor
    ~BadInterface() { }
    
    // Fat interface - too many responsibilities
    virtual void doEverything() = 0;
    virtual void andMore() = 0;
    virtual void evenMore() = 0;
    
    // Unclear names
    virtual void func1() = 0;
    virtual int thing() = 0;
    
    // Breaking const correctness
    virtual std::string getData() = 0;  // Should be const
};
```

## 🚀 Modern C++ Alternatives

### Concepts (C++20)
```cpp
#include <concepts>

template<typename T>
concept Drawable = requires(T t) {
    t.draw();
    t.setColor(std::string{});
};

void processDrawable(Drawable auto& obj) {
    obj.draw();  // Compile-time interface checking
}
```

### std::variant for Type-Safe Unions
```cpp
#include <variant>

using Shape = std::variant<Circle, Rectangle, Triangle>;

void draw(const Shape& shape) {
    std::visit([](const auto& s) { s.draw(); }, shape);
}
```

### Function Objects and Lambdas
```cpp
// Instead of Strategy interface
using SortFunction = std::function<void(std::vector<int>&)>;

class Sorter {
    SortFunction sortFunc;
public:
    Sorter(SortFunction func) : sortFunc(func) {}
    void sort(std::vector<int>& data) { sortFunc(data); }
};

// Usage
Sorter sorter([](std::vector<int>& data) { 
    std::sort(data.begin(), data.end()); 
});
```

## 📚 Summary

- **Interfaces** define contracts through pure virtual functions
- Enable **polymorphism** and **loose coupling**
- Follow **Interface Segregation Principle** - keep interfaces small
- Use **Dependency Inversion** - depend on abstractions, not concretions
- Always include **virtual destructors** in interface classes
- Consider **modern alternatives** like concepts for compile-time interfaces
- **Dynamic casting** allows safe conversion between interfaces
- Interfaces are foundation for many **design patterns**
