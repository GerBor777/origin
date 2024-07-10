#include "Square.h"

Square::Square(int side)
    : Rectangle(side, side) {}

bool Square::check() const {
    return Rectangle::check() && (a == b && b == c && c == d);
}
