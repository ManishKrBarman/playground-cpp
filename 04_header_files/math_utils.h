#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Function declarations
int add(int a, int b);
int subtract(int a, int b);
double power(double base, int exp);

// Inline function
inline int square(int x) {
    return x * x;
}

// Constant
const double PI = 3.14159;

#endif // MATH_UTILS_H
