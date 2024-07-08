#include <iostream>
#include <string>
#include <vector>

// Базовый класс Figure
class Figure {
public:
    virtual void printInfo() const = 0; // Чисто виртуальный метод для вывода информации
    virtual ~Figure() = default; // Виртуальный деструктор
};

// Класс Triangle для треугольников
class Triangle : public Figure {
protected:
    double a, b, c;
    double A, B, C;
public:
    Triangle(double a, double b, double c, double A, double B, double C)
        : a(a), b(b), c(c), A(A), B(B), C(C) {}

    void printInfo() const override {
        std::cout << "Треугольник:\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << "\n";
    }
};

// Класс RightTriangle для прямоугольных треугольников
class RightTriangle : public Triangle {
public:
    RightTriangle(double a, double b, double c, double A, double B)
        : Triangle(a, b, c, A, B, 90) {}

    void printInfo() const override {
        std::cout << "Прямоугольный треугольник:\n";
        Triangle::printInfo();
    }
};

// Класс IsoscelesTriangle для равнобедренных треугольников
class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(double a, double b, double A, double B)
        : Triangle(a, b, a, A, B, A) {}

    void printInfo() const override {
        std::cout << "Равнобедренный треугольник:\n";
        Triangle::printInfo();
    }
};

// Класс EquilateralTriangle для равносторонних треугольников
class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(double a)
        : Triangle(a, a, a, 60, 60, 60) {}

    void printInfo() const override {
        std::cout << "Равносторонний треугольник:\n";
        Triangle::printInfo();
    }
};

// Класс Quadrangle для четырёхугольников
class Quadrangle : public Figure {
protected:
    double a, b, c, d;
    double A, B, C, D;
public:
    Quadrangle(double a, double b, double c, double d, double A, double B, double C, double D)
        : a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {}

    void printInfo() const override {
        std::cout << "Четырёхугольник:\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
    }
};

// Класс Rectangle для прямоугольников
class Rectangle : public Quadrangle {
public:
    Rectangle(double a, double b)
        : Quadrangle(a, b, a, b, 90, 90, 90, 90) {}

    void printInfo() const override {
        std::cout << "Прямоугольник:\n";
        Quadrangle::printInfo();
    }
};

// Класс Square для квадратов
class Square : public Quadrangle {
public:
    Square(double a)
        : Quadrangle(a, a, a, a, 90, 90, 90, 90) {}

    void printInfo() const override {
        std::cout << "Квадрат:\n";
        Quadrangle::printInfo();
    }
};

// Класс Parallelogram для параллелограммов
class Parallelogram : public Quadrangle {
public:
    Parallelogram(double a, double b, double A, double B)
        : Quadrangle(a, b, a, b, A, B, A, B) {}

    void printInfo() const override {
        std::cout << "Параллелограмм:\n";
        Quadrangle::printInfo();
    }
};

// Класс Rhombus для ромбов
class Rhombus : public Quadrangle {
public:
    Rhombus(double a, double A, double B)
        : Quadrangle(a, a, a, a, A, B, A, B) {}

    void printInfo() const override {
        std::cout << "Ромб:\n";
        Quadrangle::printInfo();
    }
};

// Функция для вывода информации о фигуре
void print_info(const Figure* figure) {
    figure->printInfo();
}

int main() {
    // Создание объектов каждой фигуры
    Triangle triangle(10, 20, 30, 50, 60, 70);
    RightTriangle rightTriangle(10, 20, 30, 50, 60);
    IsoscelesTriangle isoscelesTriangle(10, 20, 50, 60);
    EquilateralTriangle equilateralTriangle(30);

    Quadrangle quadrangle(10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle rectangle(10, 20);
    Square square(20);
    Parallelogram parallelogram(20, 30, 30, 40);
    Rhombus rhombus(30, 30, 40);

    // Вывод информации о каждой фигуре
    print_info(&triangle);
    print_info(&rightTriangle);
    print_info(&isoscelesTriangle);
    print_info(&equilateralTriangle);

    print_info(&quadrangle);
    print_info(&rectangle);
    print_info(&square);
    print_info(&parallelogram);
    print_info(&rhombus);

    return 0;
}
