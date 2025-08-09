## 🔧 Functions in C++

## 📝 Function Anatomy
```cpp
return_type function_name(parameter_type parameter_name) {
    // function body
    return value;  // if return_type is not void
}
```

## 🎯 Key Function Concepts

### Function Declaration vs Definition
```cpp
// Declaration (prototype) - tells compiler function exists
int add(int a, int b);

// Definition - actual implementation
int add(int a, int b) {
    return a + b;
}
```

### Parameter Passing Methods

#### 1. Pass by Value (Default)
```cpp
void func(int x) {
    x = 100;  // Only changes local copy
}
```
- **Copies** the argument value
- **Changes don't affect** original variable
- **Safe** but can be slow for large objects

#### 2. Pass by Reference
```cpp
void func(int& x) {
    x = 100;  // Changes original variable
}
```
- **No copying** - direct access to original
- **Changes affect** original variable
- **Faster** for large objects
- **Use `const&`** for read-only access: `void func(const int& x)`

#### 3. Pass by Pointer
```cpp
void func(int* x) {
    *x = 100;  // Changes value at address
}
```
- **Passes memory address**
- Can be `nullptr` (unlike references)
- Requires **dereferencing** with `*`

## 🔄 Function Overloading

Same function name, **different parameter types or count**:

```cpp
int max(int a, int b);          // Version 1
double max(double a, double b); // Version 2
int max(int a, int b, int c);   // Version 3
```

**Compiler chooses** based on arguments provided. **Cannot overload** by return type only.

## 🎨 Default Parameters

```cpp
int power(int base, int exp = 2) {  // exp defaults to 2
    // implementation
}

power(5);      // Same as power(5, 2)
power(5, 3);   // Uses provided value
```

**Rules:**
- Default parameters must be **rightmost**
- Once you provide default for one parameter, **all following must have defaults**

## 🌀 Recursion

Function calls itself:

```cpp
int factorial(int n) {
    if (n <= 1) return 1;          // Base case
    return n * factorial(n - 1);   // Recursive case
}
```

**Requirements:**
1. **Base case** - stops recursion
2. **Progress toward base case**
3. **Stack space limitation** - deep recursion can cause stack overflow

## 💾 Function Call Mechanism (Assembly Level)

### Stack Frame Creation
```
1. Push arguments onto stack (right to left)
2. Push return address
3. Push old frame pointer (EBP/RBP)
4. Set new frame pointer
5. Allocate space for local variables
```

### Function Execution
```
Stack Layout:
┌─────────────────┐ ← Higher addresses
│   Parameter 2   │
├─────────────────┤
│   Parameter 1   │
├─────────────────┤
│ Return Address  │
├─────────────────┤
│ Old Frame Ptr   │ ← Frame Pointer (EBP/RBP)
├─────────────────┤
│ Local Variable  │
└─────────────────┘ ← Stack Pointer (ESP/RSP)
```

### Return Process
```
1. Store return value in register (EAX/RAX)
2. Restore stack pointer
3. Restore old frame pointer
4. Jump to return address
5. Caller cleans parameters (if needed)
```

## 🚀 Advanced Function Features

### Lambda Functions (C++11)
```cpp
auto lambda = [](int x, int y) { return x + y; };
int result = lambda(5, 3);  // result = 8
```

### Function Pointers
```cpp
int (*operation)(int, int) = add;  // Points to add function
int result = operation(5, 3);      // Calls add(5, 3)
```

### Inline Functions
```cpp
inline int square(int x) {
    return x * x;  // Hint to compiler: expand inline
}
```
- **Reduces function call overhead**
- **Code is expanded** at call site
- Only a **hint** - compiler decides

## ⚡ Best Practices

1. **Use meaningful function names** - `calculateArea()` not `calc()`
2. **Keep functions small** - one responsibility
3. **Use `const&`** for large parameters you don't modify
4. **Declare functions before use** (prototypes in headers)
5. **Avoid deep recursion** for performance-critical code
6. **Use `[[nodiscard]]`** for functions whose return value shouldn't be ignored
7. **Prefer pass-by-reference** over pointers for non-nullable parameters

## 🔍 Common Pitfalls

### Dangling References
```cpp
int& getLocal() {
    int x = 10;
    return x;  // ❌ Returns reference to local variable!
}
```

### Missing Return Statement
```cpp
int getValue() {
    // ❌ Missing return - undefined behavior
}
```

### Function Signature Mismatch
```cpp
int add(int, int);    // Declaration
float add(int, int) { // ❌ Return type mismatch
    return 0.0f;
}
```

## 🎯 Performance Considerations

- **Pass large objects by `const&`** instead of value
- **Use `inline`** for small, frequently called functions
- **Avoid unnecessary function calls** in tight loops
- **Consider function call overhead** vs code duplication

---
<div align='center'>
If I missed anything, feel free to reach me
</div>