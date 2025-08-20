#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Base class with virtual functions
class Shape {
protected:
    std::string name;

public:
    Shape(const std::string& n) : name(n) {}
    
    // Virtual destructor
    virtual ~Shape() = default;
    
    // Pure virtual function - makes this an abstract class
    virtual double area() const = 0;
    
    // Virtual function with implementation
    virtual void display() const {
        std::cout << "Shape: " << name << std::endl;
    }
    
    // Virtual function for demonstration
    virtual void describe() const {
        std::cout << "This is a generic shape" << std::endl;
    }
    
    // Non-virtual function
    void printType() const {
        std::cout << "Type: Shape" << std::endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : Shape("Rectangle"), width(w), height(h) {}
    
    // Override pure virtual function
    double area() const override {
        return width * height;
    }
    
    // Override virtual function
    void display() const override {
        Shape::display();  // Call base class version
        std::cout << "Dimensions: " << width << " x " << height << std::endl;
    }
    
    void describe() const override {
        std::cout << "This is a rectangle with 4 right angles" << std::endl;
    }
    
    // Non-virtual function
    void printType() const {
        std::cout << "Type: Rectangle" << std::endl;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("Circle"), radius(r) {}
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    void display() const override {
        Shape::display();
        std::cout << "Radius: " << radius << std::endl;
    }
    
    void describe() const override {
        std::cout << "This is a circle with infinite rotational symmetry" << std::endl;
    }
};

// Example demonstrating virtual function table (vtable) behavior
class Base {
public:
    virtual ~Base() = default;
    
    virtual void virtualFunc() const {
        std::cout << "Base::virtualFunc()" << std::endl;
    }
    
    void nonVirtualFunc() const {
        std::cout << "Base::nonVirtualFunc()" << std::endl;
    }
    
    virtual void pureVirtual() const = 0;
};

class Derived : public Base {
public:
    void virtualFunc() const override {
        std::cout << "Derived::virtualFunc()" << std::endl;
    }
    
    void nonVirtualFunc() const {  // This hides base function
        std::cout << "Derived::nonVirtualFunc()" << std::endl;
    }
    
    void pureVirtual() const override {
        std::cout << "Derived::pureVirtual() implementation" << std::endl;
    }
};

// Demonstrating virtual function call costs
class PerformanceTest {
public:
    virtual ~PerformanceTest() = default;
    
    // Virtual function - runtime dispatch
    virtual int virtualAdd(int a, int b) const {
        return a + b;
    }
    
    // Non-virtual function - compile-time binding
    int nonVirtualAdd(int a, int b) const {
        return a + b;
    }
};

// Function templates vs virtual functions
template<typename T>
void processShape(const T& shape) {
    shape.display();  // Compile-time polymorphism
    std::cout << "Area: " << shape.area() << std::endl;
}

// Virtual function polymorphism
void processShapeVirtual(const Shape& shape) {
    shape.display();  // Runtime polymorphism
    std::cout << "Area: " << shape.area() << std::endl;
}

// Advanced: Virtual function overriding with different access levels
class AccessBase {
public:
    virtual void publicVirtual() {
        std::cout << "AccessBase::publicVirtual()" << std::endl;
    }
    
protected:
    virtual void protectedVirtual() {
        std::cout << "AccessBase::protectedVirtual()" << std::endl;
    }
};

class AccessDerived : public AccessBase {
private:
    // Can override public virtual as private
    void publicVirtual() override {
        std::cout << "AccessDerived::publicVirtual() - now private!" << std::endl;
    }
    
public:
    // Can override protected virtual as public
    void protectedVirtual() override {
        std::cout << "AccessDerived::protectedVirtual() - now public!" << std::endl;
    }
};

int main() {
    std::cout << "Virtual Functions Demo:" << std::endl;
    
    // Polymorphism with virtual functions
    std::cout << "\n--- Runtime Polymorphism ---" << std::endl;
    
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(5.0, 3.0));
    shapes.push_back(std::make_unique<Circle>(4.0));
    
    for (const auto& shape : shapes) {
        shape->display();      // Virtual function - calls overridden version
        shape->describe();     // Virtual function
        std::cout << "Area: " << shape->area() << std::endl;
        shape->printType();    // Non-virtual - always calls Shape::printType
        std::cout << std::endl;
    }
    
    // Virtual vs Non-virtual function calls
    std::cout << "\n--- Virtual vs Non-Virtual Functions ---" << std::endl;
    
    Base* basePtr = new Derived();
    
    basePtr->virtualFunc();     // Calls Derived::virtualFunc() - virtual dispatch
    basePtr->nonVirtualFunc();  // Calls Base::nonVirtualFunc() - static dispatch
    basePtr->pureVirtual();     // Calls Derived::pureVirtual()
    
    delete basePtr;
    
    // Template vs Virtual function polymorphism
    std::cout << "\n--- Template vs Virtual Polymorphism ---" << std::endl;
    
    Rectangle rect(6.0, 4.0);
    Circle circ(3.0);
    
    // Template version - compile-time polymorphism
    std::cout << "Template version:" << std::endl;
    processShape(rect);
    processShape(circ);
    
    // Virtual version - runtime polymorphism  
    std::cout << "\nVirtual version:" << std::endl;
    processShapeVirtual(rect);
    processShapeVirtual(circ);
    
    // Demonstrating access level changes
    std::cout << "\n--- Access Level Changes ---" << std::endl;
    
    AccessDerived derived;
    
    // derived.publicVirtual();  // ERROR: Now private in derived class
    derived.protectedVirtual();   // OK: Now public in derived class
    
    AccessBase* basePtr2 = &derived;
    basePtr2->publicVirtual();    // Calls derived version even though it's private
    
    // Virtual function call through different pointer types
    std::cout << "\n--- Pointer Type Behavior ---" << std::endl;
    
    Rectangle* rectPtr = new Rectangle(2.0, 3.0);
    Shape* shapePtr = rectPtr;
    
    rectPtr->printType();   // Rectangle::printType() - static binding
    shapePtr->printType();  // Shape::printType() - static binding (non-virtual)
    
    rectPtr->display();     // Rectangle::display() - virtual dispatch  
    shapePtr->display();    // Rectangle::display() - virtual dispatch
    
    delete rectPtr;
    
    std::cout << "\n--- Pure Virtual Function Restriction ---" << std::endl;
    // Shape* abstractShape = new Shape("test");  // ERROR: Cannot instantiate
    Shape* concreteShape = new Circle(2.0);       // OK: Circle implements pure virtual
    concreteShape->display();
    delete concreteShape;
    
    return 0;
}
