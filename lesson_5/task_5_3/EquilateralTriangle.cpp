#include "EquilateralTriangle.h"

EquilateralTriangle::EquilateralTriangle(int side)
    : Triangle(side, side, side, 60, 60, 60) {}

bool EquilateralTriangle::check() const {
    return Triangle::check() && (a == b && b == c) && (A == 60 && B == 60 && C == 60);
}
