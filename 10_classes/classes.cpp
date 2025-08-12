#include <iostream>
#include <string>

class Rectangle {
private:
    double width;
    double height;

public:
    // Constructor
    Rectangle(double w, double h) : width(w), height(h) {
        std::cout << "Rectangle created: " << width << "x" << height << std::endl;
    }
    
    // Default constructor
    Rectangle() : width(0), height(0) {
        std::cout << "Default rectangle created" << std::endl;
    }
    
    // Destructor
    ~Rectangle() {
        std::cout << "Rectangle destroyed" << std::endl;
    }
    
    // Member functions
    double getArea() const {
        return width * height;
    }
    
    double getPerimeter() const {
        return 2 * (width + height);
    }
    
    // Setters with validation
    void setWidth(double w) {
        if (w > 0) {
            width = w;
        }
    }
    
    void setHeight(double h) {
        if (h > 0) {
            height = h;
        }
    }
    
    // Getters
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
    // Display function
    void display() const {
        std::cout << "Rectangle: " << width << "x" << height 
                  << ", Area: " << getArea() << std::endl;
    }
};

// Simple class demonstrating different access levels
class Student {
public:
    std::string name;
    int age;
    
    Student(const std::string& n, int a) : name(n), age(a) {}
    
    void introduce() const {
        std::cout << "Hi, I'm " << name << " and I'm " << age << " years old." << std::endl;
    }
};

int main() {
    std::cout << "Classes Demo:" << std::endl;
    
    // Creating objects
    Rectangle rect1(5.0, 3.0);
    rect1.display();
    
    // Using default constructor
    Rectangle rect2;
    rect2.setWidth(4.0);
    rect2.setHeight(6.0);
    rect2.display();
    
    // Student object
    Student student("Alice", 20);
    student.introduce();
    student.age = 21;  // Public member can be modified
    student.introduce();
    
    // Objects are destroyed when going out of scope
    std::cout << "Exiting main - objects will be destroyed" << std::endl;
    
    return 0;
}