## 📁 Header Files in C++

## 🎯 Purpose of Header Files

Header files (`.h` or `.hpp`) contain:
- **Function declarations** (prototypes)
- **Class declarations**
- **Constants and macros**
- **Template definitions**
- **Inline functions**

**Separate interface from implementation** - users only need to know what functions exist, not how they work.

## 🔧 Basic Header Structure

### math_utils.h
```cpp
#ifndef MATH_UTILS_H  // Header guard start
#define MATH_UTILS_H

// Function declarations
int add(int a, int b);
int subtract(int a, int b);

// Constants
const double PI = 3.14159;

// Inline functions
inline int square(int x) {
    return x * x;
}

#endif // MATH_UTILS_H  // Header guard end
```

### math_utils.cpp
```cpp
#include "math_utils.h"  // Include our header

// Function definitions
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}
```

### main.cpp
```cpp
#include <iostream>
#include "math_utils.h"  // Include our header

int main() {
    int result = add(5, 3);
    std::cout << result << std::endl;
    return 0;
}
```

## 🛡️ Header Guards

**Problem**: Including same header multiple times causes redefinition errors.

**Solution**: Header guards prevent multiple inclusions.

### Traditional Method
```cpp
#ifndef HEADER_NAME_H
#define HEADER_NAME_H
// header content
#endif
```

### Modern Method (C++11)
```cpp
#pragma once
// header content
```

## 🎯 Include Types

### System Headers (Standard Library)
```cpp
#include <iostream>  // Angle brackets for system headers
#include <vector>
#include <string>
```

### User Headers (Your Files)
```cpp
#include "math_utils.h"   // Quotes for user headers
#include "my_class.h"
```

**Search Order:**
- `<>`: System include directories first
- `""`: Current directory first, then system directories

## ⚡ Compilation Process with Headers

### Single File Compilation
```bash
# Direct compilation (works for small projects)
g++ main.cpp math_utils.cpp -o program.exe
```

### Separate Compilation
```bash
# Step 1: Compile to object files
g++ -c math_utils.cpp -o math_utils.o
g++ -c main.cpp -o main.o

# Step 2: Link object files
g++ math_utils.o main.o -o program.exe
```

## 💾 What Happens During Preprocessing

### Before Preprocessing
```cpp
// main.cpp
#include "math_utils.h"

int main() {
    int result = add(5, 3);
    return 0;
}
```

### After Preprocessing
```cpp
// main.i (preprocessed file)
// Contents of math_utils.h are inserted here:
int add(int a, int b);
int subtract(int a, int b);
const double PI = 3.14159;
inline int square(int x) { return x * x; }

int main() {
    int result = add(5, 3);  // Now compiler knows add() exists
    return 0;
}
```

## 🔍 Common Header Patterns

### Forward Declarations
```cpp
// Instead of including entire header
class MyClass;  // Forward declaration

void processClass(MyClass* obj);  // Only needs to know name exists
```

### Include What You Use
```cpp
// ❌ Don't rely on transitive includes
#include "A.h"  // A.h includes <vector>
// std::vector<int> v;  // Might work but fragile

// ✅ Explicitly include what you use
#include "A.h"
#include <vector>  // Explicit dependency
std::vector<int> v;  // Clear and robust
```

## 🚀 Advanced Header Concepts

### Template Headers
```cpp
// math_templates.h
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;  // Must be in header
}
```

**Templates must be defined in headers** because compiler needs full definition to instantiate.

### Namespace in Headers
```cpp
// math_utils.h
namespace MathUtils {
    int add(int a, int b);
    const double PI = 3.14159;
}
```

### Header-Only Libraries
```cpp
// All code in header file
// math_utils.hpp
namespace Math {
    inline int add(int a, int b) {
        return a + b;
    }
}
```

## 🎯 Best Practices

### 1. Minimize Dependencies
- **Forward declare** when possible instead of including
- **Include only what you need**

### 2. Header Guard Naming
```cpp
#ifndef PROJECT_MODULE_FILENAME_H
#define PROJECT_MODULE_FILENAME_H
// Example: MYAPP_MATH_UTILS_H
#endif
```

### 3. What Goes in Headers vs Source Files

**Headers (.h/.hpp):**
- Function declarations
- Class declarations  
- Template definitions
- Inline functions
- Constants (`const`/`constexpr`)
- Macros

**Source files (.cpp):**
- Function definitions
- Class method definitions
- Global variable definitions
- Static variables

### 4. Include Order
```cpp
// Recommended order:
#include "local_header.h"     // 1. Related header first
#include <system_headers>     // 2. System headers
#include "other_local.h"      // 3. Other project headers
```

## 🔍 Common Problems and Solutions

### Multiple Definition Error
```cpp
// ❌ Problem: defining variable in header
// utils.h
int globalVar = 42;  // Defined in header

// ✅ Solution: declare in header, define in source
// utils.h
extern int globalVar;  // Declaration only

// utils.cpp
int globalVar = 42;    // Definition
```

### Circular Dependencies
```cpp
// ❌ Problem: A.h includes B.h, B.h includes A.h

// ✅ Solution: Use forward declarations
// A.h
class B;  // Forward declaration
class A {
    B* ptr;  // Only need to know B exists
};
```

### Large Compile Times
- **Use forward declarations** instead of includes when possible
- **Minimize template usage** in headers
- **Consider precompiled headers** for large projects
- **Use `#pragma once`** for faster header guards

## 📊 Memory and Performance Impact

### Header Size Matters
- **Large headers** = longer compile times
- **Many includes** = more preprocessing work
- **Template-heavy headers** = code bloat

### Inline Functions
```cpp
inline int fastSquare(int x) {
    return x * x;  // Expanded at call site
}
```
- **No function call overhead**
- **But increases executable size**
- Compiler decides whether to actually inline

## 🛠️ Tools for Header Management

### Analyze Dependencies
```bash
# Show preprocessor output
g++ -E main.cpp | wc -l  # Count lines after preprocessing

# Show include tree
g++ -H main.cpp 2>&1 | head -20
```

### Check for Unused Headers
- Use tools like `include-what-you-use`
- Modern IDEs can highlight unused includes

---
<div align='center'>
If I missed anything, feel free to reach me
</div>