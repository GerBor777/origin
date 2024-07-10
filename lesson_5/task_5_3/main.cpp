#include <iostream>
#include "Figure.h"
#include "Triangle.h"
#include "RightTriangle.h"
#include "IsoscelesTriangle.h"
#include "EquilateralTriangle.h"
#include "Quadrilateral.h"
#include "Rectangle.h"
#include "Square.h"
#include "Parallelogram.h"
#include "Rhombus.h"

void printFigureInfo(const Figure& figure) {
    figure.printInfo();
    std::cout << (figure.check() ? "Правильная\n" : "Неправильная\n") << std::endl;
}

int main() {
    Triangle triangle(10, 20, 30, 50, 60, 70);
    RightTriangle rightTriangle(10, 20, 30, 50, 90);
    IsoscelesTriangle isoscelesTriangle(10, 20, 50, 60);
    EquilateralTriangle equilateralTriangle(30);
    Quadrilateral quadrilateral(10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle rectangle(10, 20);
    Square square(20);
    Parallelogram parallelogram(20, 30, 30, 40);
    Rhombus rhombus(30, 30, 40);

    printFigureInfo(triangle);
    printFigureInfo(rightTriangle);
    printFigureInfo(isoscelesTriangle);
    printFigureInfo(equilateralTriangle);
    printFigureInfo(quadrilateral);
    printFigureInfo(rectangle);
    printFigureInfo(square);
    printFigureInfo(parallelogram);
    printFigureInfo(rhombus);

    return 0;
}
