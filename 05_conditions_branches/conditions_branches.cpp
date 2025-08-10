#include <iostream>
#include <string>

int main() {
    std::cout << "Conditions & Branches Demo:" << std::endl;
    
    int score = 85;
    char grade;
    
    // If-else if-else
    if (score >= 90) {
        grade = 'A';
    } else if (score >= 80) {
        grade = 'B';
    } else if (score >= 70) {
        grade = 'C';
    } else if (score >= 60) {
        grade = 'D';
    } else {
        grade = 'F';
    }
    
    std::cout << "Score: " << score << ", Grade: " << grade << std::endl;
    
    // Ternary operator
    std::string result = (score >= 60) ? "Pass" : "Fail";
    std::cout << "Result: " << result << std::endl;
    
    // Switch statement
    int day = 3;
    std::string dayName;
    
    switch (day) {
        case 1:
            dayName = "Monday";
            break;
        case 2:
            dayName = "Tuesday";
            break;
        case 3:
            dayName = "Wednesday";
            break;
        case 4:
            dayName = "Thursday";
            break;
        case 5:
            dayName = "Friday";
            break;
        case 6:
        case 7:
            dayName = "Weekend";
            break;
        default:
            dayName = "Invalid day";
    }
    
    std::cout << "Day " << day << " is " << dayName << std::endl;
    
    // Logical operators
    int age = 25;
    bool hasLicense = true;
    bool canDrive = (age >= 18) && hasLicense;
    
    std::cout << "Age: " << age << ", Has license: " << std::boolalpha << hasLicense;
    std::cout << " -> Can drive: " << canDrive << std::endl;
    
    // Short-circuit evaluation
    int x = 0;
    if (x != 0 && (10 / x) > 1) {  // Second condition not evaluated if x == 0
        std::cout << "This won't execute" << std::endl;
    } else {
        std::cout << "Short-circuit prevented division by zero" << std::endl;
    }
    
    return 0;
}