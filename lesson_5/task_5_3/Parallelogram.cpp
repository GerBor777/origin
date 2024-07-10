#include "Parallelogram.h"

Parallelogram::Parallelogram(int a, int b, int A, int B)
    : Quadrilateral(a, b, a, b, A, B, A, B) {}

bool Parallelogram::check() const {
    return Quadrilateral::check() && (a == c) && (b == d) && (A == C) && (B == D);
}
