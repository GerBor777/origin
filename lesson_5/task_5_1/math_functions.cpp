#include "math_functions.h"
#include <cmath>

// Определения функций для математических операций
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        throw std::invalid_argument("Division by zero");
    }
}

double power(double base, double exponent) {
    return std::pow(base, exponent);
}
