#include <iostream>
#include <string>
#include <iomanip>

int main() {
    // Integer types
    int age = 25;                    // 32-bit signed integer
    long long population = 8000000000LL;  // 64-bit signed integer
    short temperature = -15;         // 16-bit signed integer
    unsigned int score = 95;         // 32-bit unsigned integer
    
    // Floating-point types
    float pi = 3.14159f;            // 32-bit floating point
    double precision = 3.141592653589793;  // 64-bit floating point
    long double extended = 3.141592653589793238L;  // Extended precision
    
    // Character types
    char grade = 'A';               // 8-bit character
    wchar_t unicode = L'π';         // Wide character
    char16_t utf16 = u'€';          // UTF-16 character
    char32_t utf32 = U'🚀';         // UTF-32 character
    
    // Boolean type
    bool isPassing = true;          // true or false
    bool isActive = false;
    
    // String (from std::string)
    std::string name = "John Doe";
    std::string course = "C++ Programming";
    
    // TYPE INFERENCE WITH AUTO
    
    auto autoInt = 42;              // Deduced as int
    auto autoDouble = 3.14;         // Deduced as double
    auto autoString = std::string("Hello");  // Deduced as std::string
    auto autoChar = 'X';            // Deduced as char
    
    // CONSTANTS
   
    const int MAX_SCORE = 100;      // Compile-time constant
    const double GRAVITY = 9.81;    // Physical constant
    constexpr int ARRAY_SIZE = 10;  // Compile-time expression
    
    // VARIABLE INITIALIZATION
    
    // Direct initialization
    int a(10);
    double b(3.14);
    
    // Uniform initialization (C++11)
    int c{15};
    double d{2.718};
    std::string e{"Modern C++"};
    
    // Copy initialization
    int f = 20;
    double g = 1.414;
    
    // OUTPUT WITH FORMATTING
    
    std::cout << "=== FUNDAMENTAL DATA TYPES ===" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    
    std::cout << "Integer types:" << std::endl;
    std::cout << "  age (int): " << age << std::endl;
    std::cout << "  population (long long): " << population << std::endl;
    std::cout << "  temperature (short): " << temperature << std::endl;
    std::cout << "  score (unsigned): " << score << std::endl;
    
    std::cout << "\nFloating-point types:" << std::endl;
    std::cout << "  pi (float): " << pi << std::endl;
    std::cout << "  precision (double): " << precision << std::endl;
    std::cout << "  extended (long double): " << extended << std::endl;
    
    std::cout << "\nCharacter types:" << std::endl;
    std::cout << "  grade (char): " << grade << std::endl;
    std::cout << "  unicode (wchar_t): " << static_cast<int>(unicode) << std::endl;
    
    std::cout << "\nBoolean type:" << std::endl;
    std::cout << "  isPassing: " << std::boolalpha << isPassing << std::endl;
    std::cout << "  isActive: " << isActive << std::endl;
    
    std::cout << "\nString type:" << std::endl;
    std::cout << "  name: " << name << std::endl;
    std::cout << "  course: " << course << std::endl;
    
    std::cout << "\n=== AUTO TYPE DEDUCTION ===" << std::endl;
    std::cout << "autoInt: " << autoInt << " (deduced as int)" << std::endl;
    std::cout << "autoDouble: " << autoDouble << " (deduced as double)" << std::endl;
    std::cout << "autoString: " << autoString << " (deduced as string)" << std::endl;
    std::cout << "autoChar: " << autoChar << " (deduced as char)" << std::endl;
    
    std::cout << "\n=== CONSTANTS ===" << std::endl;
    std::cout << "MAX_SCORE: " << MAX_SCORE << std::endl;
    std::cout << "GRAVITY: " << GRAVITY << std::endl;
    std::cout << "ARRAY_SIZE: " << ARRAY_SIZE << std::endl;
    
    std::cout << "\n=== INITIALIZATION METHODS ===" << std::endl;
    std::cout << "Direct init - a: " << a << ", b: " << b << std::endl;
    std::cout << "Uniform init - c: " << c << ", d: " << d << ", e: " << e << std::endl;
    std::cout << "Copy init - f: " << f << ", g: " << g << std::endl;
    
    // VARIABLE SCOPE DEMO
    
    std::cout << "\n=== SCOPE DEMONSTRATION ===" << std::endl;
    
    {   // Inner scope
        int localVar = 100;
        std::cout << "Inside block - localVar: " << localVar << std::endl;
        std::cout << "Inside block - can access age: " << age << std::endl;
    }   // localVar is destroyed here
    
    // std::cout << localVar;  // Error: localVar not accessible here
    
    return 0;
}