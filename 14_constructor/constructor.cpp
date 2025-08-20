#include <iostream>
#include <string>
#include <vector>

class Student {
private:
    std::string name;
    int age;
    double gpa;

public:
    // Default constructor
    Student() : name("Unknown"), age(0), gpa(0.0) {
        std::cout << "Default constructor called" << std::endl;
    }
    
    // Parameterized constructor
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), gpa(g) {
        std::cout << "Parameterized constructor called for " << name << std::endl;
    }
    
    // Copy constructor
    Student(const Student& other) 
        : name(other.name), age(other.age), gpa(other.gpa) {
        std::cout << "Copy constructor called for " << name << std::endl;
    }
    
    // Move constructor (C++11)
    Student(Student&& other) noexcept
        : name(std::move(other.name)), age(other.age), gpa(other.gpa) {
        std::cout << "Move constructor called" << std::endl;
        other.age = 0;
        other.gpa = 0.0;
    }
    
    // Destructor
    ~Student() {
        std::cout << "Destructor called for " << name << std::endl;
    }
    
    void display() const {
        std::cout << "Student: " << name << ", Age: " << age << ", GPA: " << gpa << std::endl;
    }
};

// Class demonstrating constructor delegation (C++11)
class Point {
private:
    double x, y;

public:
    // Delegating constructor
    Point() : Point(0.0, 0.0) {
        std::cout << "Default Point constructor" << std::endl;
    }
    
    Point(double value) : Point(value, value) {
        std::cout << "Single value Point constructor" << std::endl;
    }
    
    // Target constructor
    Point(double x, double y) : x(x), y(y) {
        std::cout << "Two-parameter Point constructor (" << x << ", " << y << ")" << std::endl;
    }
    
    void display() const {
        std::cout << "Point(" << x << ", " << y << ")" << std::endl;
    }
};

// Class with explicit constructor
class Temperature {
private:
    double celsius;

public:
    // Explicit constructor prevents implicit conversions
    explicit Temperature(double c) : celsius(c) {}
    
    double getCelsius() const { return celsius; }
};

// Class demonstrating member initialization
class Container {
private:
    const int id;           // Must be initialized
    std::vector<int> data;  // Has default constructor
    int& reference;         // Must be initialized

public:
    Container(int id, int& ref) : id(id), reference(ref) {
        data.reserve(10);
        std::cout << "Container " << id << " created" << std::endl;
    }
    
    void display() const {
        std::cout << "Container ID: " << id << ", Reference: " << reference << std::endl;
    }
};

int main() {
    std::cout << "Constructors Demo:" << std::endl;
    
    // Default constructor
    Student s1;
    s1.display();
    
    // Parameterized constructor
    Student s2("Alice", 20, 3.8);
    s2.display();
    
    // Copy constructor
    Student s3 = s2;  // Copy initialization
    Student s4(s2);   // Direct initialization
    s3.display();
    
    // Move constructor (using temporary object)
    Student s5 = Student("Bob", 22, 3.5);
    s5.display();
    
    std::cout << "\n--- Constructor Delegation ---" << std::endl;
    
    Point p1;           // Default -> Delegating -> Target
    Point p2(5.0);      // Single value -> Delegating -> Target
    Point p3(3.0, 4.0); // Direct target constructor
    
    std::cout << "\n--- Explicit Constructor ---" << std::endl;
    
    Temperature t1(25.0);  // OK: Direct initialization
    // Temperature t2 = 30.0;  // ERROR: Implicit conversion prevented
    
    std::cout << "Temperature: " << t1.getCelsius() << "°C" << std::endl;
    
    std::cout << "\n--- Member Initialization ---" << std::endl;
    
    int value = 42;
    Container c1(1, value);
    c1.display();
    
    return 0;
    // Destructors called automatically in reverse order
}
