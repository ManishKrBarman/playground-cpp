#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Base class
class Animal {
protected:  // Protected: accessible by derived classes
    std::string name;
    int age;

public:
    Animal(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Animal constructor: " << name << std::endl;
    }
    
    virtual ~Animal() {  // Virtual destructor for proper cleanup
        std::cout << "Animal destructor: " << name << std::endl;
    }
    
    // Virtual function - can be overridden
    virtual void makeSound() const {
        std::cout << name << " makes some sound" << std::endl;
    }
    
    virtual void move() const {
        std::cout << name << " moves around" << std::endl;
    }
    
    // Non-virtual function
    void sleep() const {
        std::cout << name << " is sleeping" << std::endl;
    }
    
    // Getters
    std::string getName() const { return name; }
    int getAge() const { return age; }
};

// Public inheritance - "is-a" relationship
class Dog : public Animal {
private:
    std::string breed;

public:
    Dog(const std::string& n, int a, const std::string& b) 
        : Animal(n, a), breed(b) {  // Call base constructor
        std::cout << "Dog constructor: " << name << " (" << breed << ")" << std::endl;
    }
    
    ~Dog() {
        std::cout << "Dog destructor: " << name << std::endl;
    }
    
    // Override virtual function
    void makeSound() const override {
        std::cout << name << " barks: Woof! Woof!" << std::endl;
    }
    
    void move() const override {
        std::cout << name << " runs on four legs" << std::endl;
    }
    
    // Dog-specific function
    void wagTail() const {
        std::cout << name << " wags tail happily" << std::endl;
    }
    
    std::string getBreed() const { return breed; }
};

class Cat : public Animal {
public:
    Cat(const std::string& n, int a) : Animal(n, a) {
        std::cout << "Cat constructor: " << name << std::endl;
    }
    
    ~Cat() {
        std::cout << "Cat destructor: " << name << std::endl;
    }
    
    void makeSound() const override {
        std::cout << name << " meows: Meow! Meow!" << std::endl;
    }
    
    void move() const override {
        std::cout << name << " sneaks silently" << std::endl;
    }
    
    // Cat-specific function
    void purr() const {
        std::cout << name << " purrs contentedly" << std::endl;
    }
};

// Multiple inheritance example
class Flyable {
public:
    virtual ~Flyable() = default;
    
    virtual void fly() const {
        std::cout << "Flying through the air" << std::endl;
    }
};

class Swimmable {
public:
    virtual ~Swimmable() = default;
    
    virtual void swim() const {
        std::cout << "Swimming in water" << std::endl;
    }
};

// Duck inherits from Animal, Flyable, and Swimmable
class Duck : public Animal, public Flyable, public Swimmable {
public:
    Duck(const std::string& n, int a) : Animal(n, a) {
        std::cout << "Duck constructor: " << name << std::endl;
    }
    
    ~Duck() {
        std::cout << "Duck destructor: " << name << std::endl;
    }
    
    void makeSound() const override {
        std::cout << name << " quacks: Quack! Quack!" << std::endl;
    }
    
    void fly() const override {
        std::cout << name << " flies with webbed feet tucked" << std::endl;
    }
    
    void swim() const override {
        std::cout << name << " swims with webbed feet" << std::endl;
    }
};

// Abstract base class (interface-like)
class Shape {
protected:
    std::string color;

public:
    Shape(const std::string& c) : color(c) {}
    virtual ~Shape() = default;
    
    // Pure virtual function - makes this an abstract class
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    
    // Concrete function
    std::string getColor() const { return color; }
    
    virtual void display() const {
        std::cout << "Shape color: " << color << std::endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(const std::string& c, double w, double h) 
        : Shape(c), width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    void display() const override {
        Shape::display();  // Call base class function
        std::cout << "Rectangle: " << width << "x" << height << std::endl;
    }
};

// Function demonstrating polymorphism
void demonstratePolymorphism(const std::vector<std::unique_ptr<Animal>>& animals) {
    std::cout << "\n--- Polymorphism Demo ---" << std::endl;
    
    for (const auto& animal : animals) {
        animal->makeSound();  // Calls overridden version
        animal->move();       // Calls overridden version
        animal->sleep();      // Calls base class version
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "Inheritance Demo:" << std::endl;
    
    // Basic inheritance
    std::cout << "\n--- Basic Inheritance ---" << std::endl;
    Dog myDog("Buddy", 3, "Golden Retriever");
    myDog.makeSound();
    myDog.wagTail();
    myDog.sleep();  // Inherited from Animal
    
    std::cout << "\n--- Constructor/Destructor Chain ---" << std::endl;
    {
        Cat myCat("Whiskers", 2);
        myCat.makeSound();
        myCat.purr();
    }  // Destructor chain: Cat -> Animal
    
    // Multiple inheritance
    std::cout << "\n--- Multiple Inheritance ---" << std::endl;
    Duck myDuck("Donald", 1);
    myDuck.makeSound();
    myDuck.fly();
    myDuck.swim();
    
    // Polymorphism with base class pointers
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>("Rex", 4, "German Shepherd"));
    animals.push_back(std::make_unique<Cat>("Mittens", 2));
    animals.push_back(std::make_unique<Duck>("Daffy", 1));
    
    demonstratePolymorphism(animals);
    
    // Abstract class usage
    std::cout << "\n--- Abstract Class ---" << std::endl;
    // Shape shape;  // ERROR: Cannot instantiate abstract class
    
    Rectangle rect("Red", 5.0, 3.0);
    rect.display();
    std::cout << "Area: " << rect.area() << std::endl;
    std::cout << "Perimeter: " << rect.perimeter() << std::endl;
    
    // Upcasting and downcasting
    std::cout << "\n--- Casting ---" << std::endl;
    Animal* animalPtr = new Dog("Max", 5, "Labrador");
    animalPtr->makeSound();  // Calls Dog::makeSound() due to virtual function
    
    // Downcasting (should use dynamic_cast in real code)
    Dog* dogPtr = static_cast<Dog*>(animalPtr);
    dogPtr->wagTail();
    
    delete animalPtr;
    
    return 0;
}
