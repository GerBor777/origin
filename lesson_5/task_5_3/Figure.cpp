#include "Figure.h"
#include <iostream>

Figure::Figure(int sides) : sides(sides) {}

void Figure::printInfo() const {
    std::cout << "Фигура:\n";
    std::cout << "Количество сторон: " << sides << "\n";
}

bool Figure::check() const {
    return sides == 0;
}
