## Basic workflow
```
Source Code (.cpp/.h)
     ↓
Preprocessing
     ↓
Compilation
     ↓
Assembly
     ↓
Linking
     ↓
Executable (Binary)
     ↓
Execution
```
## 📝 Source Code

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```
## 🔍 Preprocessing
Handled by the C++ preprocessor:
- It expands all macros `#define`
- Replaces all `#include` with the actual contents of header files
- Handles conditionals `#ifdef, #ifndef, etc.`

**Result** : a `translation unit` — a huge `.i` file with everything expanded.

To get this `.i` file, try this cmd :
```
g++ -E main.cpp -o main.i          # Preprocess only: expand macros and includes
```
## 🧠 Compilation
This step converts the preprocessed code to assembly language
- Parses syntax `tokens, grammar`
- Checks types, builds AST `abstract syntax tree`
- Optimizes code `if requested`
- Emits low-level `.s` file `assembly`

To get this `.s` file, try this cmd :
```
g++ -S main.i -o main.s       # Compile to assembly: convert C++ to assembly language
```
## 🧬 Assembly
The assembler converts `.s` into a `.o` `object file` — this is machine code, but incomplete.
- Pure binary instructions
- Doesn’t yet contain full addresses for function calls or variables
To get this `.o` file, try this cmd :
```
g++ -c main.s -o main.o       # Assemble: convert assembly to machine code object file
```
At this point, each `.cpp` file becomes a `.o` object file after being compiled and assembled

## 🧩 Linking
The linker takes `.o` files and libraries, resolves symbols, and creates a complete executable:
- Resolves external function calls, like `std::cout`
- Merges multiple `.o` files into a single executable
- Adds startup code `_start, main wrapper, CRT (C Runtime)`
- Links against standard C++ library `libstdc++` and system libraries
- Assigns final memory addresses to all symbols
- Creates the final executable with proper entry point
To get this executable file, try this cmd :
```
g++ main.o -o main.exe       # Link: create final executable from object files
```

## 🏁 Execution
To run the executable, try this cmd :
```
main.exe       # Execute the compiled program
# OR
.\main.exe     # Alternative way to execute on Windows
```


## 🔄 Recap All Commands
```
# Step 1: Preprocess
g++ -E main.cpp -o main.i

# Step 2: Compile to Assembly
g++ -S main.i -o main.s

# Step 3: Assemble to Object File
g++ -c main.s -o main.o

# Step 4: Link to Executable
g++ main.o -o main.exe

# Step 5: Run it
main.exe

# Get all the files at once `saves intermediate files`
g++ -save-temps main.cpp -o main.exe
```
---
<div align='center'>
If I missed anything, feel free to reach me
</div>