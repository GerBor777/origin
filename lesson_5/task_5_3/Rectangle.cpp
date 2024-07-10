#include "Rectangle.h"

Rectangle::Rectangle(int a, int b)
    : Quadrilateral(a, b, a, b, 90, 90, 90, 90) {}

bool Rectangle::check() const {
    return Quadrilateral::check() && (A == 90 && B == 90 && C == 90 && D == 90) && (a == c) && (b == d);
}
