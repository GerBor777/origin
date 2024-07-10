#include "Quadrilateral.h"
#include <iostream>

Quadrilateral::Quadrilateral(int a, int b, int c, int d, int A, int B, int C, int D)
    : Figure(4), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {}

void Quadrilateral::printInfo() const {
    Figure::printInfo();
    std::cout << "Четырёхугольник:\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}

bool Quadrilateral::check() const {
    return Figure::check() && (A + B + C + D == 360);
}
