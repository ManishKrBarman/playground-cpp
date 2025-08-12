## ⚡ Static in C++

## 🎯 What Does Static Mean?

The `static` keyword has **different meanings** depending on context:
1. **Static local variables** - persist between function calls
2. **Static global variables/functions** - internal linkage (file scope)
3. **Static class members** - shared among all instances of the class

## 🔧 Static Local Variables

### Function-Local Static
```cpp
void counter() {
    static int count = 0;  // Initialized only ONCE (first call)
    count++;
    std::cout << "Called " << count << " times" << std::endl;
}

counter();  // Output: Called 1 times
counter();  // Output: Called 2 times  
counter();  // Output: Called 3 times
```

**Key characteristics:**
- **Initialized only once** (on first function call)
- **Retains value** between function calls
- **Zero-initialized** if no initializer provided
- **Thread-safe initialization** in C++11+

### Use Cases
```cpp
// Singleton pattern implementation
Database& getDatabase() {
    static Database instance;  // Created once, persists
    return instance;
}

// Cache/memoization
int fibonacci(int n) {
    static std::unordered_map<int, int> cache;
    
    if (cache.find(n) != cache.end()) {
        return cache[n];  // Return cached result
    }
    
    int result = (n <= 1) ? n : fibonacci(n-1) + fibonacci(n-2);
    cache[n] = result;
    return result;
}
```

## 🌐 Static Global Variables and Functions

### Internal Linkage
```cpp
// file1.cpp
static int fileCounter = 0;        // Only visible in this file
static void helperFunction() {     // Only callable from this file
    fileCounter++;
}

// file2.cpp  
static int fileCounter = 100;      // Different variable! (file-local)
// Cannot call helperFunction() from file1.cpp
```

**Benefits:**
- **Prevents naming conflicts** between files
- **Hides implementation details**
- **Compiler optimization** opportunities

### Modern Alternative: Anonymous Namespace
```cpp
// Modern C++ equivalent
namespace {  // Anonymous namespace
    int fileCounter = 0;        // Internal linkage
    void helperFunction() {     // Internal linkage
        fileCounter++;
    }
}
```

## 🏗️ Static Class Members

### Static Data Members
```cpp
class Player {
private:
    static int totalPlayers;    // Declaration (shared by all instances)
    std::string name;
    
public:
    Player(const std::string& n) : name(n) {
        totalPlayers++;         // Increment shared counter
    }
    
    ~Player() {
        totalPlayers--;         // Decrement on destruction
    }
    
    static int getTotalPlayers() {  // Static member function
        return totalPlayers;
    }
};

// Definition required outside class (exactly once)
int Player::totalPlayers = 0;

// Usage
Player p1("Alice");
Player p2("Bob");
std::cout << Player::getTotalPlayers();  // Output: 2 (no object needed)
```

### Static Member Functions
```cpp
class MathUtils {
public:
    static double pi() {
        return 3.14159;
    }
    
    static int factorial(int n) {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    }
    
    // ❌ Cannot access non-static members
    // static void invalidFunction() {
    //     instanceVariable = 10;  // Error!
    // }
    
private:
    int instanceVariable;  // Non-static member
};

// Called without creating object
double piValue = MathUtils::pi();
int fact5 = MathUtils::factorial(5);
```

## 💾 Memory Layout and Lifetime

### Static Variable Storage
```cpp
// Memory layout:
void function() {
    int localVar;           // Stack memory (destroyed on return)
    static int staticVar;   // Static storage area (persistent)
}

int globalVar;              // Static storage area (program lifetime)
static int fileStaticVar;  // Static storage area (program lifetime)
```

**Memory Sections:**
```
┌─────────────────┐ ← High Address
│      Stack      │ ← Local variables
├─────────────────┤
│      Heap       │ ← Dynamic allocations (new/malloc)
├─────────────────┤
│   Static/BSS    │ ← Static variables (initialized/uninitialized)
├─────────────────┤
│   Data Section  │ ← Global initialized variables
├─────────────────┤
│   Code Section  │ ← Program instructions
└─────────────────┘ ← Low Address
```

### Initialization Order
```cpp
// Global static variables initialized before main()
static int globalStatic = initialize();  // Called before main

int main() {
    static int localStatic = getValue();  // Initialized on first call
    
    // Function-local statics initialized in order of first call
}
```

**Static Initialization Order Fiasco:**
```cpp
// file1.cpp
static MyClass obj1(someValue);  // Initialized first?

// file2.cpp  
static MyClass obj2(obj1.getValue());  // Depends on obj1 - undefined order!

// ✅ Solution: Use local static
MyClass& getObj1() {
    static MyClass obj1(someValue);  // Initialized on first call
    return obj1;
}
```

## 🚀 Advanced Static Concepts

### Static Template Members
```cpp
template<typename T>
class Singleton {
private:
    static T* instance;
    
public:
    static T& getInstance() {
        if (!instance) {
            instance = new T();
        }
        return *instance;
    }
};

// Each template instantiation gets its own static member
template<typename T>
T* Singleton<T>::instance = nullptr;

// Usage
auto& intSingleton = Singleton<int>::getInstance();
auto& stringSingleton = Singleton<std::string>::getInstance();
// Different instances for different types
```

### Thread Safety (C++11+)
```cpp
// Thread-safe static initialization
MyClass& getSingleton() {
    static MyClass instance;  // Thread-safe initialization in C++11+
    return instance;
}

// Before C++11, needed explicit synchronization
MyClass& getUnsafeSingleton() {
    static std::mutex mutex;
    static MyClass* instance = nullptr;
    
    std::lock_guard<std::mutex> lock(mutex);
    if (!instance) {
        instance = new MyClass();
    }
    return *instance;
}
```

### Constexpr Static (C++11+)
```cpp
class Constants {
public:
    static constexpr double PI = 3.14159;        // Compile-time constant
    static constexpr int MAX_SIZE = 1000;
    
    // Complex compile-time computation
    static constexpr int fibonacci(int n) {
        return (n <= 1) ? n : fibonacci(n-1) + fibonacci(n-2);
    }
};

// Can use directly without definition (for integral/enum types)
int array[Constants::MAX_SIZE];  // Compile-time size
```

## 🎯 Best Practices

### 1. Prefer Static Local to Global Static
```cpp
// ❌ Global static - initialization order issues
static Database database;

// ✅ Function static - lazy initialization
Database& getDatabase() {
    static Database db;  // Initialized on first call
    return db;
}
```

### 2. Use Static for Utility Functions
```cpp
class StringUtils {
public:
    static std::string trim(const std::string& str) {
        // Utility function - no need for instance
    }
    
    static bool isEmpty(const std::string& str) {
        return str.empty();
    }
};

// Clear that these don't need object state
std::string cleaned = StringUtils::trim(input);
```

### 3. Static Member Initialization
```cpp
class Config {
public:
    static const int VERSION = 1;           // ✅ Integral const can be initialized in class
    static constexpr double PI = 3.14159;  // ✅ constexpr can be initialized in class
    
private:
    static std::string appName;             // ✅ Requires definition in .cpp file
    static std::vector<int> data;           // ✅ Requires definition in .cpp file
};

// In .cpp file:
std::string Config::appName = "MyApp";
std::vector<int> Config::data = {1, 2, 3, 4, 5};
```

### 4. Avoid Static for Objects with Destructors
```cpp
// ❌ Potential issues with destruction order
static std::vector<int> globalVector;

// ✅ Better - use local static in function
std::vector<int>& getGlobalVector() {
    static std::vector<int> vector;
    return vector;
}
```

## 🔍 Common Pitfalls

### 1. Static Initialization Order
```cpp
// file1.cpp
static int value1 = 10;

// file2.cpp
static int value2 = value1 + 5;  // ❌ Undefined! value1 might not be initialized yet
```

### 2. Static Member Definition Forgotten
```cpp
class Example {
    static int count;  // Declaration only
};

// ❌ Forgot definition - linker error!
// int Example::count = 0;  // Need this in .cpp file
```

### 3. Thread Safety Assumptions
```cpp
class Counter {
    static int count;
public:
    static void increment() {
        count++;  // ❌ Not thread-safe!
    }
};

// ✅ Thread-safe version
class SafeCounter {
    static std::atomic<int> count;
public:
    static void increment() {
        count++;  // Atomic operation
    }
};
```

## 📊 Performance Considerations

### Static vs Instance Members
```cpp
class Example {
    static int staticVar;     // One copy for all instances
    int instanceVar;          // One copy per instance
    
public:
    static void staticFunc() {    // No 'this' pointer overhead
        // Faster call - no object reference needed
    }
    
    void instanceFunc() {         // Has 'this' pointer
        // Slight overhead for 'this' pointer
    }
};
```

### Memory Usage
```cpp
class Logger {
    static std::ofstream logFile;  // Shared among all instances
    std::string instanceName;      // Per-instance storage
};

// 1000 Logger objects:
// Static: 1 file handle
// Instance: 1000 strings + 1 shared file handle
```

---
<div align='center'>
If I missed anything, feel free to reach me
</div>