#include "RightTriangle.h"

RightTriangle::RightTriangle(int a, int b, int c, int A, int B)
    : Triangle(a, b, c, A, B, 90) {}

bool RightTriangle::check() const {
    return Triangle::check() && (C == 90);
}
