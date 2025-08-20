#include <iostream>
#include <string>

// Traditional enum (C-style)
enum Color {
    RED,      // 0
    GREEN,    // 1
    BLUE      // 2
};

// Enum with explicit values
enum Status {
    PENDING = 10,
    PROCESSING = 20,
    COMPLETED = 30,
    FAILED = -1
};

// Scoped enum (enum class) - C++11
enum class Direction {
    North,
    South, 
    East,
    West
};

// Scoped enum with specific type
enum class Priority : char {
    Low = 'L',
    Medium = 'M',
    High = 'H',
    Critical = 'C'
};

// Function using enum
std::string getColorName(Color c) {
    switch (c) {
        case RED:   return "Red";
        case GREEN: return "Green";
        case BLUE:  return "Blue";
        default:    return "Unknown";
    }
}

// Function using scoped enum
std::string getDirectionName(Direction d) {
    switch (d) {
        case Direction::North: return "North";
        case Direction::South: return "South";
        case Direction::East:  return "East";
        case Direction::West:  return "West";
        default: return "Unknown";
    }
}

int main() {
    std::cout << "Enums Demo:" << std::endl;
    
    // Traditional enum usage
    Color favColor = BLUE;
    std::cout << "Favorite color: " << getColorName(favColor) << std::endl;
    std::cout << "Color value: " << favColor << std::endl;
    
    // Status enum
    Status taskStatus = PROCESSING;
    std::cout << "Task status value: " << taskStatus << std::endl;
    
    // Scoped enum usage
    Direction playerDirection = Direction::North;
    std::cout << "Player direction: " << getDirectionName(playerDirection) << std::endl;
    
    // Priority enum
    Priority taskPriority = Priority::High;
    std::cout << "Task priority: " << static_cast<char>(taskPriority) << std::endl;
    
    // Enum comparisons
    if (favColor == BLUE) {
        std::cout << "Blue is your favorite!" << std::endl;
    }
    
    if (playerDirection == Direction::North) {
        std::cout << "Heading north!" << std::endl;
    }
    
    // Implicit conversion (traditional enum)
    int colorValue = RED;  // Allowed
    std::cout << "RED as int: " << colorValue << std::endl;
    
    // No implicit conversion (scoped enum)
    // int dirValue = Direction::North;  // Compilation error!
    int dirValue = static_cast<int>(Direction::North);  // Explicit cast needed
    std::cout << "North as int: " << dirValue << std::endl;
    
    return 0;
}
