## 🧬 Inheritance in C++

## 🎯 What is Inheritance?

Inheritance allows a class (derived/child) to **inherit properties and behaviors** from another class (base/parent). It enables:
- **Code reuse** - don't repeat common functionality
- **Polymorphism** - treat objects of different types uniformly
- **"Is-a" relationship** modeling

```cpp
class Animal {      // Base class
    // Common functionality
};

class Dog : public Animal {  // Derived class
    // Dog inherits from Animal + adds specific functionality
};
```

## 🔧 Types of Inheritance

### Public Inheritance ("is-a" relationship)
```cpp
class Vehicle {
protected:
    int speed;
public:
    void start() { std::cout << "Vehicle started" << std::endl; }
};

class Car : public Vehicle {  // Car IS-A Vehicle
public:
    void honk() { std::cout << "Car honks" << std::endl; }
};

Car myCar;
myCar.start();  // Inherited from Vehicle
myCar.honk();   // Car-specific method
```

### Protected Inheritance (rarely used)
```cpp
class Base { /* ... */ };
class Derived : protected Base { /* ... */ };
// Base's public members become protected in Derived
```

### Private Inheritance ("implemented-in-terms-of")
```cpp
class Engine { /* ... */ };
class Car : private Engine { /* ... */ };
// Engine functionality used internally, not exposed
```

## 🏗️ Constructor and Destructor Chain

### Construction Order
```cpp
class Base {
public:
    Base(int x) { std::cout << "Base constructor" << std::endl; }
    virtual ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Derived : public Base {
public:
    Derived(int x, int y) : Base(x) {  // Must call base constructor
        std::cout << "Derived constructor" << std::endl;
    }
    
    ~Derived() { std::cout << "Derived destructor" << std::endl; }
};

// Construction: Base → Derived
// Destruction: Derived → Base
```

## 🎭 Virtual Functions and Polymorphism

### Virtual Functions
```cpp
class Animal {
public:
    virtual void makeSound() const {  // Virtual function
        std::cout << "Some animal sound" << std::endl;
    }
    
    void sleep() const {  // Non-virtual function
        std::cout << "Animal sleeps" << std::endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() const override {  // Override virtual function
        std::cout << "Woof!" << std::endl;
    }
};
```

### Polymorphism in Action
```cpp
void playWithAnimal(Animal& animal) {
    animal.makeSound();  // Calls appropriate version based on actual type
}

Dog myDog;
Cat myCat;

playWithAnimal(myDog);  // Calls Dog::makeSound()
playWithAnimal(myCat);  // Calls Cat::makeSound()
```

### Virtual Destructor (Essential!)
```cpp
class Base {
public:
    virtual ~Base() { }  // Virtual destructor ensures proper cleanup
};

class Derived : public Base {
private:
    int* data;
public:
    ~Derived() { delete[] data; }  // Will be called even through base pointer
};

Base* ptr = new Derived();
delete ptr;  // Both destructors called correctly
```

## 🚫 Pure Virtual Functions (Abstract Classes)

### Abstract Base Class
```cpp
class Shape {  // Abstract class - cannot be instantiated
public:
    virtual double area() const = 0;      // Pure virtual function
    virtual double perimeter() const = 0; // Pure virtual function
    
    virtual ~Shape() = default;
    
    // Can have non-pure virtual functions
    virtual void display() const {
        std::cout << "This is a shape" << std::endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
};

// Shape s;     // ERROR: Cannot instantiate abstract class
Circle c(5.0);  // OK: Circle implements all pure virtual functions
```

## 🔗 Multiple Inheritance

### Basic Multiple Inheritance
```cpp
class Flyable {
public:
    virtual void fly() { std::cout << "Flying" << std::endl; }
};

class Swimmable {
public:
    virtual void swim() { std::cout << "Swimming" << std::endl; }
};

class Duck : public Animal, public Flyable, public Swimmable {
public:
    void fly() override { std::cout << "Duck flies" << std::endl; }
    void swim() override { std::cout << "Duck swims" << std::endl; }
};

Duck duck;
duck.fly();   // From Flyable
duck.swim();  // From Swimmable
duck.move();  // From Animal
```

### Diamond Problem and Virtual Inheritance
```cpp
class Animal { /* ... */ };
class Mammal : virtual public Animal { /* ... */ };  // Virtual inheritance
class Bird : virtual public Animal { /* ... */ };    // Virtual inheritance
class Bat : public Mammal, public Bird { /* ... */ }; // Only one Animal instance
```

## 🔍 Access Levels in Inheritance

### Member Access
```cpp
class Base {
private:
    int privateData;    // Only Base can access
protected:
    int protectedData;  // Base and derived classes can access  
public:
    int publicData;     // Everyone can access
};

class Derived : public Base {
public:
    void accessMembers() {
        // privateData = 1;    // ERROR: Cannot access private members
        protectedData = 2;     // OK: Can access protected members
        publicData = 3;        // OK: Can access public members
    }
};
```

### Inheritance Access Levels
| Base Access | Public Inheritance | Protected Inheritance | Private Inheritance |
|-------------|-------------------|----------------------|-------------------|
| public      | public            | protected            | private           |
| protected   | protected         | protected            | private           |
| private     | not accessible    | not accessible       | not accessible    |

## 🎯 Best Practices

### ✅ Good Practices
```cpp
class Good {
public:
    // Always virtual destructor for base classes
    virtual ~Good() = default;
    
    // Use override keyword for clarity
    virtual void doSomething() const;
};

class GoodDerived : public Good {
public:
    // Clear override intention
    void doSomething() const override;
    
    // Explicitly call base constructor when needed
    GoodDerived(int x) : Good(x) {}
};
```

### ❌ Avoid
```cpp
class Bad {
public:
    ~Bad() { }  // Non-virtual destructor in base class - dangerous!
    
    virtual void method();
};

class BadDerived : public Bad {
public:
    void method();  // Missing override - easy to make mistakes
    
    // Implicit base constructor call might not be what you want
    BadDerived(int x) { }
};
```

## 🧪 Advanced Concepts

### Function Hiding
```cpp
class Base {
public:
    virtual void func(int x) { std::cout << "Base::func(int)" << std::endl; }
    void func(double x) { std::cout << "Base::func(double)" << std::endl; }
};

class Derived : public Base {
public:
    void func(int x) override { std::cout << "Derived::func(int)" << std::endl; }
    // Base::func(double) is hidden!
    
    // To make base versions visible:
    using Base::func;  // Brings all Base::func overloads into scope
};
```

### Covariant Return Types
```cpp
class Animal {
public:
    virtual Animal* clone() const { return new Animal(*this); }
};

class Dog : public Animal {
public:
    Dog* clone() const override {  // Covariant return type
        return new Dog(*this);
    }
};
```

## 🔄 When to Use Inheritance

### ✅ Use Inheritance When:
- True **"is-a" relationship** exists
- You need **polymorphic behavior**
- **Code reuse** makes sense
- You're modeling a **natural hierarchy**

### ❌ Don't Use Inheritance When:
- **"has-a" relationship** (use composition instead)
- Just for **code reuse** without logical relationship
- **Diamond problem** becomes complex
- **Interface segregation** would be better

### Composition vs Inheritance
```cpp
// Inheritance: "Car IS-A Vehicle"
class Car : public Vehicle { /* ... */ };

// Composition: "Car HAS-A Engine"
class Car {
    Engine engine;  // Composition
    // ...
};
```

## 📚 Summary

- **Public inheritance** models "is-a" relationships
- **Virtual functions** enable polymorphism
- **Pure virtual functions** create abstract classes
- **Virtual destructors** essential for proper cleanup
- **Multiple inheritance** possible but complex
- **Prefer composition** over inheritance when relationship isn't clearly "is-a"
- **Use override keyword** for clarity and safety
