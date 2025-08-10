## 🔀 Conditional Statements and Branching

## 🎯 Basic Conditional Structure

### If Statement
```cpp
if (condition) {
    // Execute if condition is true
}
```

### If-Else
```cpp
if (condition) {
    // Execute if true
} else {
    // Execute if false
}
```

### If-Else If-Else Chain
```cpp
if (condition1) {
    // First condition
} else if (condition2) {
    // Second condition  
} else if (condition3) {
    // Third condition
} else {
    // Default case
}
```

## ⚡ Ternary Operator

**Syntax**: `condition ? value_if_true : value_if_false`

```cpp
int max = (a > b) ? a : b;
std::string result = (score >= 60) ? "Pass" : "Fail";
```

**Benefits**: 
- **Concise** for simple conditions
- **Can be used in expressions**
- **Avoids code duplication**

## 🔄 Switch Statement

```cpp
switch (expression) {
    case value1:
        // statements
        break;
    case value2:
        // statements  
        break;
    default:
        // default statements
}
```

### Switch Characteristics
- **Expression must be integral type** (int, char, enum)
- **Case values must be compile-time constants**
- **Break prevents fall-through**
- **Default case is optional but recommended**

### Fall-Through Behavior
```cpp
switch (grade) {
    case 'A':
    case 'B':
        std::cout << "Excellent!" << std::endl;
        break;  // Both A and B execute this
    case 'C':
        std::cout << "Good" << std::endl;
        break;
}
```

## 🔍 Logical Operators

| Operator | Name | Example | Description |
|----------|------|---------|-------------|
| `&&` | AND | `a && b` | True if both true |
| `\|\|` | OR | `a \|\| b` | True if either true |
| `!` | NOT | `!a` | Inverts boolean value |

### Short-Circuit Evaluation

**AND (`&&`)**: If left side is false, right side is **not evaluated**
```cpp
if (ptr != nullptr && ptr->isValid()) {
    // Safe - ptr checked first
}
```

**OR (`||`)**: If left side is true, right side is **not evaluated**
```cpp
if (found || search()) {
    // search() only called if found is false
}
```

## 💾 Assembly Level Understanding

### If Statement Assembly
```cpp
// C++ Code
if (x > 5) {
    y = 10;
}
```

```assembly
; Assembly equivalent (simplified x86-64)
cmp    rax, 5          ; Compare x with 5
jle    .skip           ; Jump if Less or Equal (x <= 5)
mov    rbx, 10         ; y = 10
.skip:
```

### Switch Statement Assembly
```cpp
switch (value) {
    case 1: result = 10; break;
    case 2: result = 20; break;
    case 3: result = 30; break;
}
```

**Compiler optimizations:**
- **Jump table** for dense cases (1,2,3,4...)
- **Binary search** for sparse cases
- **If-else chain** for very few cases

```assembly
; Jump table approach (dense cases)
mov    rax, [value]
cmp    rax, 3
ja     .default        ; Jump if above 3
jmp    [jump_table + rax*8]

jump_table:
    dq .case0, .case1, .case2, .case3
```

## 🚀 Advanced Branching Concepts

### Constexpr If (C++17)
```cpp
template<typename T>
void process(T value) {
    if constexpr (std::is_integral_v<T>) {
        // Compile-time branch for integers
        std::cout << "Processing integer: " << value << std::endl;
    } else {
        // Compile-time branch for non-integers
        std::cout << "Processing non-integer" << std::endl;
    }
}
```

### Structured Bindings with If (C++17)
```cpp
if (auto [success, result] = someFunction(); success) {
    std::cout << "Success: " << result << std::endl;
}
```

### Init Statement in If (C++17)
```cpp
if (auto it = map.find(key); it != map.end()) {
    std::cout << "Found: " << it->second << std::endl;
}
```

## ⚡ Performance Considerations

### Branch Prediction
Modern CPUs **predict which branch** will be taken:

```cpp
// Predictable pattern - fast
for (int i = 0; i < 1000000; i++) {
    if (i % 2 == 0) {  // Alternating pattern
        // even
    } else {
        // odd
    }
}

// Random pattern - slower due to mispredictions
for (int i = 0; i < 1000000; i++) {
    if (rand() % 2) {  // Random pattern
        // random branch
    }
}
```

### Branch-Free Code
```cpp
// Branching version
int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

// Branch-free version (sometimes faster)
int max(int a, int b) {
    return a > b ? a : b;  // May compile to conditional move
}
```

## 🎯 Best Practices

### 1. Condition Ordering
```cpp
// ✅ Put most likely condition first
if (commonCondition) {
    // Most frequent case
} else if (rareCondition) {
    // Less frequent case
}
```

### 2. Use Switch for Multiple Values
```cpp
// ❌ Long if-else chain
if (status == STATUS_OK) { /* */ }
else if (status == STATUS_ERROR) { /* */ }
else if (status == STATUS_PENDING) { /* */ }

// ✅ Switch statement
switch (status) {
    case STATUS_OK: /* */ break;
    case STATUS_ERROR: /* */ break;  
    case STATUS_PENDING: /* */ break;
}
```

### 3. Avoid Deep Nesting
```cpp
// ❌ Deep nesting
if (condition1) {
    if (condition2) {
        if (condition3) {
            // deep nesting
        }
    }
}

// ✅ Early returns
if (!condition1) return;
if (!condition2) return;
if (!condition3) return;
// main logic here
```

### 4. Use Braces Consistently
```cpp
// ❌ Dangerous
if (condition)
    statement1;
    statement2;  // Not part of if!

// ✅ Always use braces
if (condition) {
    statement1;
    statement2;
}
```

## 🔍 Common Pitfalls

### Assignment vs Comparison
```cpp
// ❌ Assignment instead of comparison
if (x = 5) {  // Assigns 5 to x, always true
    // Always executes
}

// ✅ Comparison
if (x == 5) {  // Compares x with 5
    // Executes if x equals 5
}
```

### Floating Point Comparison
```cpp
// ❌ Direct comparison
if (float_val == 0.1) {  // Might fail due to precision
    // Unreliable
}

// ✅ Epsilon comparison
const double EPSILON = 1e-9;
if (std::abs(float_val - 0.1) < EPSILON) {
    // Reliable comparison
}
```

### Switch Fall-Through
```cpp
switch (value) {
    case 1:
        doSomething();
        // ❌ Missing break - falls through to case 2
    case 2:
        doSomethingElse();  // Executes for both case 1 and 2
        break;
}
```

## 🛠️ Debugging Tips

### Use Explicit Parentheses
```cpp
// Unclear precedence
if (a && b || c && d) { /* confusing */ }

// Clear precedence  
if ((a && b) || (c && d)) { /* clear */ }
```

### Consider Using Enums
```cpp
enum class State { IDLE, RUNNING, PAUSED, STOPPED };

switch (currentState) {
    case State::IDLE: /* */ break;
    case State::RUNNING: /* */ break;
    // Compiler warns about missing cases
}
```

---
<div align='center'>
If I missed anything, feel free to reach me
</div>