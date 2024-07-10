#include "Triangle.h"
#include <iostream>

Triangle::Triangle(int a, int b, int c, int A, int B, int C)
    : Figure(3), a(a), b(b), c(c), A(A), B(B), C(C) {}

void Triangle::printInfo() const {
    Figure::printInfo();
    std::cout << "Треугольник:\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << "\n";
}

bool Triangle::check() const {
    return Figure::check() && (A + B + C == 180);
}
