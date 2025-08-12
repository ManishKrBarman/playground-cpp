#include <iostream>
#include <string>
#include <cmath>

// Simple struct for data storage
struct Point {
    double x, y;  // Public by default
    
    // Constructor
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    // Member function
    double distanceFromOrigin() const {
        return std::sqrt(x*x + y*y);
    }
};

// Struct with mixed access levels
struct Student {
    std::string name;    // Public by default
    int age;
    
private:
    double gpa;          // Private member
    
public:
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), gpa(g) {}
    
    double getGPA() const { return gpa; }
    void setGPA(double g) { if (g >= 0.0 && g <= 4.0) gpa = g; }
};

// Plain Old Data (POD) struct
struct Color {
    unsigned char r, g, b, a;
};

// Struct for function return
struct Rectangle {
    double width, height;
    
    double area() const { return width * height; }
    double perimeter() const { return 2 * (width + height); }
};

int main() {
    std::cout << "Structs Demo:" << std::endl;
    
    // Creating and using Point
    Point p1;                    // Default constructor
    Point p2(3.0, 4.0);         // Parameterized constructor
    
    std::cout << "Point p1: (" << p1.x << ", " << p1.y << ")" << std::endl;
    std::cout << "Point p2: (" << p2.x << ", " << p2.y << ")" << std::endl;
    std::cout << "Distance from origin: " << p2.distanceFromOrigin() << std::endl;
    
    // Direct member access (public by default)
    p1.x = 1.5;
    p1.y = 2.5;
    std::cout << "Modified p1: (" << p1.x << ", " << p1.y << ")" << std::endl;
    
    // Student with private members
    Student student("Alice", 20, 3.8);
    std::cout << "Student: " << student.name << ", Age: " << student.age;
    std::cout << ", GPA: " << student.getGPA() << std::endl;
    
    // POD struct initialization
    Color red = {255, 0, 0, 255};
    Color blue{0, 0, 255, 255};    // Uniform initialization
    
    std::cout << "Red color: RGB(" << (int)red.r << ", " << (int)red.g 
              << ", " << (int)red.b << ")" << std::endl;
    
    // Struct with member functions
    Rectangle rect{5.0, 3.0};
    std::cout << "Rectangle: " << rect.width << "x" << rect.height;
    std::cout << ", Area: " << rect.area() << std::endl;
    
    return 0;
}