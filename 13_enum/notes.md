## 🏷️ Enums in C++

## 🎯 What are Enums?

Enums (enumerations) are user-defined types that consist of **named constants**. C++ has two types:
- **Traditional enum** (C-style) - can implicitly convert to int
- **Scoped enum** (enum class) - type-safe, no implicit conversion

```cpp
enum Color { RED, GREEN, BLUE };        // Traditional enum
enum class Status { Active, Inactive }; // Scoped enum (C++11)
```

## 🔧 Traditional Enum

### Basic Declaration
```cpp
enum Color {
    RED,      // 0 (default)
    GREEN,    // 1
    BLUE      // 2
};

Color c = RED;
int value = c;  // Implicit conversion to int (0)
```

### Custom Values
```cpp
enum HttpStatus {
    OK = 200,
    NOT_FOUND = 404,
    SERVER_ERROR = 500
};
```

**Key characteristics:**
- **Global scope** - names pollute enclosing namespace
- **Implicit conversion** to int
- **Can be used in arithmetic** operations

## 🛡️ Scoped Enum (enum class)

### Basic Declaration
```cpp
enum class Direction {
    North, South, East, West
};

Direction d = Direction::North;  // Must use scope resolution
// int value = d;  // ERROR: No implicit conversion
int value = static_cast<int>(d);  // Explicit cast required
```

### With Specific Underlying Type
```cpp
enum class Priority : char {
    Low = 'L',
    Medium = 'M', 
    High = 'H'
};
```

**Key advantages:**
- **Type safe** - no implicit conversions
- **Scoped names** - no namespace pollution
- **Can specify underlying type** explicitly
- **Stronger type checking**

## ⚖️ Traditional vs Scoped Enum

| Feature | Traditional Enum | Scoped Enum |
|---------|------------------|-------------|
| Implicit conversion | ✅ Yes | ❌ No |
| Namespace pollution | ⚠️ Yes | ✅ No |
| Type safety | ⚠️ Weak | ✅ Strong |
| Scope resolution | Optional | Required |
| Underlying type | int (default) | Customizable |

## 🎯 Best Practices

### ✅ Good Practices
```cpp
// Use scoped enums for type safety
enum class State { Running, Paused, Stopped };

// Use descriptive names
enum class LogLevel { Debug, Info, Warning, Error };

// Specify underlying type when needed
enum class ErrorCode : uint16_t { Success = 0, InvalidInput = 1000 };
```

### ❌ Avoid
```cpp
// Don't use traditional enums in modern C++
enum Color { RED, GREEN, BLUE };  // Pollutes namespace

// Don't rely on implicit conversions
int value = RED;  // Unclear intent
```

## 🔍 Common Use Cases

### State Machines
```cpp
enum class GameState {
    Menu, Playing, Paused, GameOver
};
```

### Error Handling
```cpp
enum class Result {
    Success, FileNotFound, AccessDenied, OutOfMemory
};
```

### Configuration Options
```cpp
enum class LogLevel {
    None, Error, Warning, Info, Debug, Verbose
};
```

## 🧪 Advanced Features

### Forward Declaration
```cpp
enum class Color;        // Forward declare scoped enum
enum class Color : int;  // With underlying type
```

### Switch Statements
```cpp
enum class Operation { Add, Subtract, Multiply, Divide };

int calculate(int a, int b, Operation op) {
    switch (op) {
        case Operation::Add:      return a + b;
        case Operation::Subtract: return a - b;
        case Operation::Multiply: return a * b;
        case Operation::Divide:   return a / b;
    }
    return 0;  // Handle all cases for safety
}
```

### Bitwise Operations (Flag Enums)
```cpp
enum class Permissions {
    None = 0,
    Read = 1,
    Write = 2, 
    Execute = 4
};

// Enable bitwise operations
Permissions operator|(Permissions a, Permissions b) {
    return static_cast<Permissions>(
        static_cast<int>(a) | static_cast<int>(b)
    );
}
```

## 📚 Summary

- **Traditional enums** are legacy C-style, avoid in modern C++
- **Scoped enums** provide type safety and clean namespaces
- Use **explicit underlying types** when memory or interop matters
- **Always handle all cases** in switch statements
- **Prefer scoped enums** for new code
