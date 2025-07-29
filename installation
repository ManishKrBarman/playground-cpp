# C++ Development Environment Setup Guide

This guide will walk you through setting up a complete C++ development environment on Windows.

## Prerequisites

- Windows 10 or later
- Administrator privileges for installing software
- Stable internet connection for downloads

## Step 1: Install Visual Studio Code

1. **Download VS Code:**
   - Visit https://code.visualstudio.com/
   - Click "Download for Windows"
   - Choose the appropriate installer (User or System installer)

2. **Install VS Code:**
   - Run the downloaded installer
   - Accept the license agreement
   - Choose installation location (default is recommended)
   - Select additional tasks:
     - ✅ Add "Open with Code" action to Windows Explorer file context menu
     - ✅ Add "Open with Code" action to Windows Explorer directory context menu
     - ✅ Register Code as an editor for supported file types
     - ✅ Add to PATH (requires shell restart)
   - Click "Install"

## Step 2: Install C++ Compiler (Choose ONE option)

### Option A: Visual Studio Build Tools (Recommended)

1. **Download Visual Studio Installer:**
   - Visit https://visualstudio.microsoft.com/downloads/
   - Scroll down to "Tools for Visual Studio"
   - Download "Build Tools for Visual Studio 2022"

2. **Install C++ Build Tools:**
   - Run the installer
   - Select "C++ build tools" workload
   - In the installation details, ensure these are selected:
     - ✅ MSVC v143 - VS 2022 C++ x64/x86 build tools
     - ✅ Windows 11 SDK (latest version)
     - ✅ CMake tools for Visual Studio
   - Click "Install"

### Option B: MinGW-w64 (Alternative)

1. **Download MSYS2:**
   - Visit https://www.msys2.org/
   - Download the installer for x86_64
   - Run the installer and follow the setup wizard

2. **Install MinGW-w64:**
   - Open MSYS2 terminal
   - Update package database: `pacman -Syu`
   - Close terminal when prompted and reopen
   - Install MinGW-w64: `pacman -S mingw-w64-x86_64-gcc`
   - Install additional tools: `pacman -S mingw-w64-x86_64-gdb mingw-w64-x86_64-make`

3. **Add to PATH:**
   - Add `C:\msys64\mingw64\bin` to your system PATH environment variable

## Step 3: Install Essential VS Code Extensions

1. **Open VS Code**
2. **Install C/C++ Extension Pack:**
   - Press `Ctrl+Shift+X` to open Extensions view
   - Search for "C/C++ Extension Pack"
   - Install the extension by Microsoft (includes multiple C++ tools)

3. **Recommended Additional Extensions:**
   - **CMake Tools** - For CMake project management
   - **Code Runner** - For quick code execution
   - **Better Comments** - Enhanced comment styling `optional`
   - **GitLens** - Enhanced Git capabilities

## Step 4: Configure VS Code for C++

1. **Create a workspace folder:**
   ```cmd
   mkdir C:\cpp-projects
   cd C:\cpp-projects
   ```

2. **Open folder in VS Code:**
   - File → Open Folder → Select your cpp-projects folder

## Step 5: Create Build Configuration

### For MSVC (recommended approach):

1. **Create tasks.json:**
   - Press `Ctrl+Shift+P`
   - Type "Tasks: Configure Task"
   - Select "Create tasks.json file from template"
   - Choose "Others"

2. **Configure build task in `.vscode/tasks.json`:**
   ```json
   {
       "version": "2.0.0",
       "tasks": [
           {
               "type": "shell",
               "label": "C++: cl.exe build active file",
               "command": "cl.exe",
               "args": [
                   "/EHsc",
                   "/Fe:",
                   "${fileDirname}\\${fileBasenameNoExtension}.exe",
                   "${file}"
               ],
               "options": {
                   "cwd": "${fileDirname}"
               },
               "problemMatcher": ["$msCompile"],
               "group": {
                   "kind": "build",
                   "isDefault": true
               }
           }
       ]
   }
   ```

### For MinGW:

Configure build task in `.vscode/tasks.json`:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "shell",
            "label": "C++: g++.exe build active file",
            "command": "C:/msys64/mingw64/bin/g++.exe",
            "args": [
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": ["$gcc"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

## Step 6: Set Up Debugging

1. **Create launch.json:**
   - Press `Ctrl+Shift+P`
   - Type "Debug: Open launch.json"
   - Select "C++ (Windows)"

2. **Configure debugger in `.vscode/launch.json`:**

For MSVC:
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C++: cl.exe debug",
            "type": "cppvsdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "console": "externalTerminal",
            "preLaunchTask": "C++: cl.exe build active file"
        }
    ]
}
```

For MinGW:
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C++: g++ debug",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "miDebuggerPath": "C:/msys64/mingw64/bin/gdb.exe",
            "preLaunchTask": "C++: g++.exe build active file"
        }
    ]
}
```

## Step 7: Test Your Setup

1. **Create a test file:**
   ```cpp
   #include <iostream>
   
   int main() {
       std::cout << "Hello, C++ World!" << std::endl;
       return 0;
   }
   ```

2. **Build and run:**
   - Press `Ctrl+Shift+P`
   - Type "Tasks: Run Task"
   - Select your build task
   - Or press `Ctrl+F5` to run without debugging

## Step 8: Optional Enhancements

### Install Package Manager (vcpkg)

1. **Clone vcpkg:**
   ```cmd
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   ```

2. **Integrate with VS:**
   ```cmd
   .\vcpkg integrate install
   ```

### Install CMake (for larger projects)

1. Download from https://cmake.org/download/
2. Install with "Add CMake to PATH" option selected

## Troubleshooting

### Common Issues:

1. **Compiler not found:**
   - Verify PATH environment variable includes compiler directory
   - Restart VS Code after PATH changes

2. **IntelliSense not working:**
   - Restart VS Code and reload the window
   - Verify that C/C++ extension is properly installed and enabled

3. **Build fails:**
   - Check tasks.json configuration
   - Ensure file paths use correct separators (`\\` for Windows)

4. **Debugger issues:**
   - Verify debugger type matches your compiler (cppvsdbg for MSVC, cppdbg for GCC)
   - Check that executable was built with debug symbols

### Getting Help:

- VS Code C++ Documentation: https://code.visualstudio.com/docs/languages/cpp
- Stack Overflow: Tag questions with [visual-studio-code] and [c++]
- VS Code GitHub Issues: https://github.com/microsoft/vscode/issues

## Next Steps

Once your environment is set up:

1. Explore the sample projects in this workspace
2. Learn about debugging features in VS Code
3. Set up version control with Git
4. Consider learning CMake for larger projects
5. Explore advanced C++ features and libraries

---

## 🎯 Congratulations!

✅ Your C++ Development Environment is Ready!                
                                                              
- Compiler installed and configured                         
- VS Code optimized for C++ development                     
- Build and debug tools ready                               
- All set for your C++ coding journey

### 🚀 **Ready to Code?**

Start your first project with confidence! Your development environment is now equipped with all the essential tools for modern C++ programming.

### 💡 **Pro Tips:**
- Use `Ctrl + Shift + B` for quick builds
- Set breakpoints with `F9` for effective debugging
- Explore VS Code's command palette (`Ctrl + Shift + P`) for powerful features

**Now go create something amazing with C++!** 💪

