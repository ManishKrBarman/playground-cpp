## 🔍 Fundamental Data Types Deep Dive

### Integer Types
| Type | Size | Range | Suffix |
|------|------|-------|--------|
| `short` | 16 bits | -32,768 to 32,767 | none |
| `int` | 32 bits | -2,147,483,648 to 2,147,483,647 | none |
| `long` | 32/64 bits | Platform dependent | `L` or `l` |
| `long long` | 64 bits | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 | `LL` or `ll` |

**Unsigned Variants:**
- `unsigned short`, `unsigned int`, `unsigned long`, `unsigned long long`
- Range starts from 0 and doubles the positive range
- Example: `unsigned int` → 0 to 4,294,967,295

### Floating-Point Types
| Type | Size | Precision | Suffix |
|------|------|-----------|--------|
| `float` | 32 bits | ~7 decimal digits | `f` or `F` |
| `double` | 64 bits | ~15-17 decimal digits | none |
| `long double` | 80/128 bits | Platform dependent | `L` or `l` |

**Key Points:**
- **Always use suffix for float literals**: `3.14f` not `3.14`
- **Double is default** for decimal literals without suffix
- **Scientific notation**: `1.23e-4` (0.000123)

### Character Types
```cpp
char ascii = 'A';           // 8-bit ASCII character
wchar_t wide = L'π';        // Wide character (16/32 bit)
char16_t utf16 = u'€';      // UTF-16 character
char32_t utf32 = U'🚀';     // UTF-32 character
```

**Character Escape Sequences:**
- `'\n'` - Newline
- `'\t'` - Tab
- `'\\'` - Backslash
- `'\''` - Single quote
- `'\"'` - Double quote
- `'\0'` - Null character

## 🎯 Type Inference with `auto`

```cpp
auto x = 42;        // int
auto y = 3.14;      // double
auto z = 3.14f;     // float
auto s = "Hello";   // const char*
auto str = std::string("Hello");  // std::string
```

**Benefits:**
- **Reduces verbosity** for complex type names
- **Prevents type mismatches**
- **Easier refactoring**

**Best Practices:**
- Use when type is obvious from context
- Use for complex template types
- Avoid when it hurts readability

## 🔒 Constants and `constexpr`

### `const` vs `constexpr`
```cpp
const int runtime_const = getValue();     // Runtime constant
constexpr int compile_const = 42;         // Compile-time constant

const double PI = 3.14159;                // Runtime constant
constexpr double E = 2.71828;             // Compile-time constant
```

**Key Differences:**
- `const`: Value cannot change after initialization (runtime or compile-time)
- `constexpr`: Must be computable at compile-time

## 🎨 Variable Initialization Methods

### 1. Copy Initialization
```cpp
int x = 10;
double y = 3.14;
std::string s = "Hello";
```

### 2. Direct Initialization
```cpp
int x(10);
double y(3.14);
std::string s("Hello");
```

### 3. Uniform Initialization (C++11) - **RECOMMENDED**
```cpp
int x{10};
double y{3.14};
std::string s{"Hello"};
```

**Advantages of Uniform Initialization:**
- **Prevents narrowing conversions**
- **Works with all types consistently**
- **No most vexing parse problem**

### 4. Value Initialization
```cpp
int x{};      // Initialized to 0
double y{};   // Initialized to 0.0
bool b{};     // Initialized to false
```

## 🌍 Variable Scope and Lifetime

### Scope Types
```cpp
int global_var = 100;           // Global scope

int main() {
    int function_var = 200;     // Function scope
    
    {                           // Block scope
        int block_var = 300;

        // All three variables accessible here
    }  

    // block_var destroyed here
    // Only global_var and function_var accessible here
    
    return 0;
}   

// function_var destroyed here
// Only global_var remains
```

### Scope Rules
1. **Global scope**: Accessible everywhere in the program
2. **Function scope**: Accessible within the function
3. **Block scope**: Accessible within the `{}` block
4. **Inner scopes can access outer scope variables**
5. **Variables are destroyed when leaving their scope**

## 💾 Memory Layout

### Stack vs Heap
```cpp
// Stack allocation (automatic storage)
int x = 10;                     // On stack
int arr[100];                   // On stack

// Heap allocation (dynamic storage)
int* ptr = new int(10);         // On heap
int* array = new int[100];      // On heap
delete ptr;                     // Must manually free
delete[] array;                 // Must manually free
```

## 🔧 Advanced Variable Concepts

### Type Aliases
```cpp
using Age = int;                // Modern way (C++11)
typedef int Weight;             // Old way

Age person_age = 25;
Weight person_weight = 70;
```

### Reference Variables
```cpp
int x = 10;
int& ref = x;                   // ref is an alias for x
ref = 20;                       // Changes x to 20
```

### Pointer Variables
```cpp
int x = 10;
int* ptr = &x;                  // ptr holds address of x
*ptr = 20;                      // Changes x to 20 through pointer
```

## ⚡ Quick Commands
```bash
# Compile with all warnings
g++ -Wall -Wextra variables.cpp -o variables.exe

# Compile with debug information
g++ -g variables.cpp -o variables.exe

# Compile with optimization
g++ -O2 variables.cpp -o variables.exe

# Run the program
variables.exe
```

## 🚀 Performance Tips

1. **Use `constexpr` for compile-time constants**
2. **Prefer uniform initialization `{}`**
3. **Use `auto` for complex types**
4. **Initialize variables when declaring**
5. **Use references to avoid copying large objects**
6. **Prefer `std::string` over C-style strings**

## 🔍 Common Pitfalls

### Uninitialized Variables
```cpp
int x;                          // ❌ Undefined behavior
int y{};                        // ✅ Zero-initialized
```

### Narrowing Conversions
```cpp
int x = 3.14;                   // ❌ Truncates to 3
int y{3.14};                    // ❌ Compilation error (good!)
```

### Floating-Point Precision
```cpp
float a = 0.1f;
float b = 0.2f;
float c = a + b;                // ❌ Not exactly 0.3!
// Use epsilon for comparisons
```

## 🎯 Key Takeaways

1. **Choose appropriate data types** for your use case
2. **Always initialize variables** when declaring
3. **Use `const`/`constexpr`** for values that don't change
4. **Prefer uniform initialization** `{}` syntax
5. **Understand scope** and variable lifetime
6. **Use `auto`** judiciously for cleaner code
7. **Be aware of type conversions** and potential data loss

---

<div align='center'>
If I missed anything, feel free to reach me
</div>