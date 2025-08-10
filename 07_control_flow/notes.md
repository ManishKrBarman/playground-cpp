## 🚦 Advanced Control Flow

## 🎯 Jump Statements

### Return Statement
```cpp
int findValue(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Immediately exit function
        }
    }
    return -1;  // Default return (not found)
}
```

**Key Points:**
- **Immediately exits** the function
- **Can return a value** (if function return type is not void)
- **Multiple returns** are allowed but can reduce readability

### Break Statement

#### In Loops
```cpp
for (int i = 0; i < 100; i++) {
    if (i == 10) {
        break;  // Exit loop completely
    }
    std::cout << i << " ";
}
// Continues execution here after break
```

#### In Switch Statements
```cpp
switch (value) {
    case 1:
        doSomething();
        break;  // Prevents fall-through
    case 2:
        doSomethingElse();
        break;
    default:
        defaultAction();
}
```

#### Breaking from Nested Loops
```cpp
// ❌ Break only exits innermost loop
for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
        if (condition) {
            break;  // Only exits inner loop
        }
    }
    // Outer loop continues
}

// ✅ Using flag to break from nested loops
bool shouldExit = false;
for (int i = 0; i < 5 && !shouldExit; i++) {
    for (int j = 0; j < 5; j++) {
        if (condition) {
            shouldExit = true;
            break;
        }
    }
}

// ✅ Alternative: Use function and return
void processMatrix() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (condition) {
                return;  // Exits entire function
            }
        }
    }
}
```

### Continue Statement
```cpp
for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
        continue;  // Skip even numbers
    }
    std::cout << i << " ";  // Only odd numbers printed
}
// Output: 1 3 5 7 9
```

## 🚨 Exception Handling

### Basic Try-Catch
```cpp
try {
    int result = divide(10, 0);  // May throw exception
    std::cout << "Result: " << result << std::endl;
}
catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
}
```

### Multiple Catch Blocks
```cpp
try {
    // Code that might throw different exceptions
    riskyOperation();
}
catch (const std::runtime_error& e) {
    // Handle runtime errors
    std::cout << "Runtime error: " << e.what() << std::endl;
}
catch (const std::invalid_argument& e) {
    // Handle invalid argument errors
    std::cout << "Invalid argument: " << e.what() << std::endl;
}
catch (const std::exception& e) {
    // Handle all other standard exceptions
    std::cout << "General error: " << e.what() << std::endl;
}
catch (...) {
    // Handle any other exception
    std::cout << "Unknown error occurred" << std::endl;
}
```

### Throwing Exceptions
```cpp
double safeDivide(double a, double b) {
    if (b == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    if (a < 0 || b < 0) {
        throw std::invalid_argument("Negative arguments not allowed");
    }
    return a / b;
}
```

### RAII and Exception Safety
```cpp
class Resource {
    int* data;
public:
    Resource() : data(new int[100]) {}
    ~Resource() { delete[] data; }  // Always called, even during exception
};

void riskyFunction() {
    Resource r;  // Constructor called
    // If exception thrown here, destructor still called
    throw std::runtime_error("Something went wrong");
}  // Destructor called automatically
```

## 💾 Assembly Level Control Flow

### Jump Instructions
```cpp
// C++ Code
if (x > 5) {
    doSomething();
} else {
    doSomethingElse();
}
```

```assembly
; Assembly equivalent
    cmp    eax, 5         ; Compare x with 5
    jle    .else_branch   ; Jump Less or Equal to else
    call   doSomething    ; True branch
    jmp    .end          ; Skip else branch
.else_branch:
    call   doSomethingElse
.end:
```

### Function Call Stack
```cpp
int main() {
    functionA();    // Call functionA
    return 0;
}

void functionA() {
    functionB();    // Call functionB
}

void functionB() {
    return;         // Return to functionA
}
```

**Stack during execution:**
```
┌─────────────────┐ ← Stack grows down
│ main() frame    │
├─────────────────┤
│ functionA()     │
├─────────────────┤
│ functionB()     │ ← Current function
└─────────────────┘
```

### Exception Unwinding
When exception is thrown:
1. **Current function** searches for handler
2. If not found, **function exits** and stack unwinds  
3. **Destructors called** for local objects
4. **Process repeats** up the call stack
5. **Program terminates** if no handler found

## 🎯 Advanced Control Flow Patterns

### RAII (Resource Acquisition Is Initialization)
```cpp
// Automatic resource management
{
    std::lock_guard<std::mutex> lock(mutex);  // Acquire lock
    // Critical section
    // Lock automatically released when leaving scope
}
```

### Early Return Pattern
```cpp
// ❌ Deep nesting
void processData(Data data) {
    if (data.isValid()) {
        if (data.hasRequiredFields()) {
            if (data.passesValidation()) {
                // Process data
            }
        }
    }
}

// ✅ Early return (guard clauses)
void processData(Data data) {
    if (!data.isValid()) return;
    if (!data.hasRequiredFields()) return;
    if (!data.passesValidation()) return;
    
    // Process data - no deep nesting
}
```

### Loop-and-a-Half Pattern
```cpp
// Reading until EOF or error
while (true) {
    std::string line;
    if (!std::getline(input, line)) {
        break;  // EOF or error
    }
    processLine(line);
}
```

### State Machine Pattern
```cpp
enum class State { IDLE, RUNNING, PAUSED, STOPPED };

State currentState = State::IDLE;
bool running = true;

while (running) {
    switch (currentState) {
        case State::IDLE:
            if (startRequested) {
                currentState = State::RUNNING;
            }
            break;
            
        case State::RUNNING:
            if (pauseRequested) {
                currentState = State::PAUSED;
            } else if (stopRequested) {
                currentState = State::STOPPED;
            }
            doWork();
            break;
            
        case State::PAUSED:
            if (resumeRequested) {
                currentState = State::RUNNING;
            }
            break;
            
        case State::STOPPED:
            running = false;
            break;
    }
}
```

## 🚀 Modern C++ Control Flow (C++17/20)

### Structured Bindings
```cpp
auto [success, result] = tryOperation();
if (success) {
    std::cout << "Operation succeeded: " << result << std::endl;
}
```

### Constexpr If
```cpp
template<typename T>
void process(T value) {
    if constexpr (std::is_integral_v<T>) {
        // Compile-time branching
        std::cout << "Processing integer" << std::endl;
    } else {
        std::cout << "Processing non-integer" << std::endl;
    }
}
```

## 🎯 Best Practices

### 1. Prefer Early Returns
- **Reduces nesting**
- **Improves readability**
- **Follows "guard clause" pattern**

### 2. Use RAII for Resource Management
```cpp
// ✅ Automatic cleanup
{
    std::unique_ptr<Resource> resource = std::make_unique<Resource>();
    // Resource automatically cleaned up
}
```

### 3. Exception Safety Levels
- **No-throw guarantee**: Function never throws
- **Strong guarantee**: If exception thrown, program state unchanged
- **Basic guarantee**: No resource leaks, but state may change
- **No guarantee**: Anything can happen

### 4. Avoid goto
```cpp
// ❌ Spaghetti code
if (condition1) goto label1;
if (condition2) goto label2;
label1:
    // Code here
label2:
    // More code

// ✅ Structured alternatives
if (condition1) {
    // Handle condition1
} else if (condition2) {
    // Handle condition2
}
```

## 🔍 Performance Considerations

### Branch Prediction
```cpp
// ✅ Predictable branches perform better
if (likely_condition) {  // Branch predictor learns this pattern
    // Common case
} else {
    // Rare case
}
```

### Exception Performance
- **Zero cost** when not thrown (modern compilers)
- **Expensive** when actually thrown
- Use for **exceptional circumstances**, not normal flow

### Function Call Overhead
```cpp
// Small functions may be inlined by compiler
inline int fastFunction(int x) {
    return x * 2;  // May be expanded at call site
}
```

---
<div align='center'>
If I missed anything, feel free to reach me
</div>