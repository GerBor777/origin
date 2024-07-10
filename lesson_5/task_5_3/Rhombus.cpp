#include "Rhombus.h"

Rhombus::Rhombus(int side, int A, int B)
    : Parallelogram(side, side, A, B) {}

bool Rhombus::check() const {
    return Parallelogram::check() && (a == b && b == c && c == d);
}
