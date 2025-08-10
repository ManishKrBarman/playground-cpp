## 🔄 Loops in C++

## 🎯 For Loop

**Syntax**: `for (initialization; condition; increment/decrement)`

```cpp
for (int i = 0; i < 10; i++) {
    std::cout << i << " ";
}
```

**Execution Order:**
1. **Initialize** `i = 0`
2. **Check condition** `i < 10`  
3. **Execute body** if true
4. **Increment/decrement** `i++`
5. **Repeat steps 2-4**

### Variations
```cpp
// Multiple variables
for (int i = 0, j = 10; i < j; i++, j--) {
    // i increases, j decreases
}

// Empty sections
for (;;) {  // Infinite loop
    break;  // Need explicit break
}

// Decrementing
for (int i = 10; i > 0; i--) {
    std::cout << i << " ";
}
```

## 🔄 While Loop

**Syntax**: `while (condition)`

```cpp
int i = 0;
while (i < 10) {
    std::cout << i << " ";
    i++;  // Don't forget to modify condition variable!
}
```

**Use when**: Number of iterations is **not known in advance**

```cpp
// Reading input until valid
int input;
while (std::cin >> input && input < 0) {
    std::cout << "Please enter positive number: ";
}
```

## 🔄 Do-While Loop

**Syntax**: `do { } while (condition);`

```cpp
int choice;
do {
    std::cout << "Enter choice (1-3): ";
    std::cin >> choice;
} while (choice < 1 || choice > 3);
```

**Key difference**: **Executes at least once** (condition checked after body)

## 🚀 Range-Based For Loop (C++11)

**Syntax**: `for (type variable : container)`

```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5};

// Read-only access
for (const auto& num : numbers) {
    std::cout << num << " ";
}

// Modify elements
for (auto& num : numbers) {
    num *= 2;  // Double each element
}

// Works with arrays too
int arr[] = {10, 20, 30};
for (int value : arr) {
    std::cout << value << " ";
}
```

## 🎮 Loop Control Statements

### Break Statement
```cpp
for (int i = 0; i < 100; i++) {
    if (i == 5) {
        break;  // Exit loop completely
    }
    std::cout << i << " ";
}
// Output: 0 1 2 3 4
```

### Continue Statement  
```cpp
for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
        continue;  // Skip rest of current iteration
    }
    std::cout << i << " ";
}
// Output: 1 3 5 7 9
```

### Goto Statement (Avoid!)
```cpp
// ❌ Not recommended - breaks structured programming
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
        if (found) goto cleanup;
    }
}
cleanup:
    // Cleanup code
```

## 💾 Assembly Level Understanding

### For Loop Assembly
```cpp
// C++ Code
for (int i = 0; i < 10; i++) {
    sum += i;
}
```

```assembly
; Assembly equivalent (simplified x86-64)
    mov    eax, 0        ; i = 0
.loop_start:
    cmp    eax, 10       ; Compare i with 10
    jge    .loop_end     ; Jump if Greater or Equal (exit loop)
    add    ebx, eax      ; sum += i
    inc    eax           ; i++
    jmp    .loop_start   ; Jump back to condition check
.loop_end:
```

### Loop Unrolling Optimization
```cpp
// Original loop
for (int i = 0; i < 4; i++) {
    array[i] *= 2;
}

// Compiler might unroll to:
array[0] *= 2;
array[1] *= 2;  
array[2] *= 2;
array[3] *= 2;
// Eliminates loop overhead for small, fixed iterations
```

## 🏎️ Performance Considerations

### Cache-Friendly Loops
```cpp
// ✅ Cache-friendly (row-major order)
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        matrix[i][j] = value;  // Sequential memory access
    }
}

// ❌ Cache-unfriendly (column-major order)  
for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
        matrix[i][j] = value;  // Random memory access
    }
}
```

### Loop Invariants
```cpp
// ❌ Inefficient - recalculates size each iteration
for (int i = 0; i < vector.size(); i++) {
    // Process vector[i]
}

// ✅ Efficient - calculate size once
const size_t size = vector.size();
for (size_t i = 0; i < size; i++) {
    // Process vector[i]
}

// ✅ Even better - use range-based for
for (const auto& element : vector) {
    // Process element
}
```

### Branch Prediction in Loops
```cpp
// Predictable pattern - CPU branch predictor works well
for (int i = 0; i < 1000; i++) {
    if (i % 4 == 0) {  // Predictable pattern every 4 iterations
        // Some operation
    }
}
```

## 🎯 Advanced Loop Patterns

### Iterator Loops
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};

// Traditional iterator loop
for (auto it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << " ";
}

// Reverse iteration
for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    std::cout << *it << " ";
}
```

### Algorithm-Based Loops
```cpp
#include <algorithm>

std::vector<int> numbers = {1, 2, 3, 4, 5};

// Replace explicit loops with algorithms when possible
std::for_each(numbers.begin(), numbers.end(), [](int& n) {
    n *= 2;  // Double each element
});
```

### Infinite Loops
```cpp
// Event loop pattern
while (true) {
    Event event = getNextEvent();
    if (event.type == EXIT) break;
    processEvent(event);
}

// Alternative syntax
for (;;) {
    // Infinite loop
    if (shouldExit()) break;
}
```

## 🎯 Best Practices

### 1. Choose the Right Loop Type
- **For loop**: Known number of iterations
- **While loop**: Unknown number of iterations  
- **Do-while**: Need at least one execution
- **Range-based for**: Iterating over containers

### 2. Prefer Range-Based For
```cpp
// ❌ Traditional loop
for (size_t i = 0; i < vec.size(); i++) {
    process(vec[i]);
}

// ✅ Range-based for (cleaner, safer)
for (const auto& element : vec) {
    process(element);
}
```

### 3. Use Const References for Read-Only
```cpp
// ✅ Avoid unnecessary copies
for (const auto& item : expensiveObjects) {
    // Read-only access, no copying
}
```

### 4. Be Careful with Modifying Containers
```cpp
// ❌ Dangerous - modifying container while iterating
for (auto& item : vec) {
    if (condition) {
        vec.erase(/* ... */);  // Invalidates iterators!
    }
}

// ✅ Use explicit iterator with proper erasure
for (auto it = vec.begin(); it != vec.end();) {
    if (condition) {
        it = vec.erase(it);  // Returns next valid iterator
    } else {
        ++it;
    }
}
```

## 🔍 Common Pitfalls

### Off-by-One Errors
```cpp
// ❌ Common mistake
for (int i = 0; i <= size; i++) {  // Goes one beyond!
    arr[i] = 0;  // Buffer overflow!
}

// ✅ Correct
for (int i = 0; i < size; i++) {
    arr[i] = 0;
}
```

### Infinite Loops
```cpp
// ❌ Forgot to modify loop variable
int i = 0;
while (i < 10) {
    std::cout << i << " ";
    // Missing i++ causes infinite loop!
}
```

### Float Loop Counters
```cpp
// ❌ Avoid floating point counters due to precision issues
for (float f = 0.0; f < 1.0; f += 0.1) {
    // May not work as expected due to floating point errors
}

// ✅ Use integer counters and convert
for (int i = 0; i < 10; i++) {
    float f = i * 0.1f;
    // More reliable
}
```

### Nested Loop Performance
```cpp
// Time complexity awareness
for (int i = 0; i < n; i++) {           // O(n)
    for (int j = 0; j < n; j++) {       // O(n²)
        for (int k = 0; k < n; k++) {   // O(n³)
            // Expensive operation - consider optimization
        }
    }
}
```

---
<div align='center'>
If I missed anything, feel free to reach me
</div>