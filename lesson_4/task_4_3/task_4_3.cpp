#include <iostream>
#include <string>
#include <vector>

// Базовый класс Figure
class Figure {
protected:
    int sides_count;

public:
    Figure(int sides) : sides_count(sides) {}

    virtual void print_info() const {
        std::cout << "Фигура:\n";
        std::cout << "Количество сторон: " << sides_count << "\n";
    }

    virtual bool check() const {
        return sides_count == 0;
    }

    virtual ~Figure() = default;
};

// Класс Triangle для треугольников
class Triangle : public Figure {
protected:
    double a, b, c;
    double A, B, C;

public:
    Triangle(double a, double b, double c, double A, double B, double C)
        : Figure(3), a(a), b(b), c(c), A(A), B(B), C(C) {}

    void print_info() const override {
        std::cout << "Треугольник:\n";
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << "\n";
    }

    bool check() const override {
        return Figure::check() || (A + B + C == 180);
    }
};

// Класс RightTriangle для прямоугольных треугольников
class RightTriangle : public Triangle {
public:
    RightTriangle(double a, double b, double c, double A, double B)
        : Triangle(a, b, c, A, B, 90) {}

    void print_info() const override {
        std::cout << "Прямоугольный треугольник:\n";
        Triangle::print_info();
    }

    bool check() const override {
        return Triangle::check() && C == 90;
    }
};

// Класс IsoscelesTriangle для равнобедренных треугольников
class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(double a, double b, double A, double B)
        : Triangle(a, b, a, A, B, A) {}

    void print_info() const override {
        std::cout << "Равнобедренный треугольник:\n";
        Triangle::print_info();
    }

    bool check() const override {
        return Triangle::check() && a == c && A == C;
    }
};

// Класс EquilateralTriangle для равносторонних треугольников
class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(double a)
        : Triangle(a, a, a, 60, 60, 60) {}

    void print_info() const override {
        std::cout << "Равносторонний треугольник:\n";
        Triangle::print_info();
    }

    bool check() const override {
        return Triangle::check() && a == b && b == c && A == B && B == C && A == 60;
    }
};

// Класс Quadrangle для четырёхугольников
class Quadrangle : public Figure {
protected:
    double a, b, c, d;
    double A, B, C, D;

public:
    Quadrangle(double a, double b, double c, double d, double A, double B, double C, double D)
        : Figure(4), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {}

    void print_info() const override {
        std::cout << "Четырёхугольник:\n";
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
    }

    bool check() const override {
        return Figure::check() || (A + B + C + D == 360);
    }
};

// Класс Rectangle для прямоугольников
class Rectangle : public Quadrangle {
public:
    Rectangle(double a, double b)
        : Quadrangle(a, b, a, b, 90, 90, 90, 90) {}

    void print_info() const override {
        std::cout << "Прямоугольник:\n";
        Quadrangle::print_info();
    }

    bool check() const override {
        return Quadrangle::check() && a == c && b == d && A == 90 && B == 90 && C == 90 && D == 90;
    }
};

// Класс Square для квадратов
class Square : public Quadrangle {
public:
    Square(double a)
        : Quadrangle(a, a, a, a, 90, 90, 90, 90) {}

    void print_info() const override {
        std::cout << "Квадрат:\n";
        Quadrangle::print_info();
    }

    bool check() const override {
        return Quadrangle::check() && a == b && b == c && c == d && A == 90 && B == 90 && C == 90 && D == 90;
    }
};

// Класс Parallelogram для параллелограммов
class Parallelogram : public Quadrangle {
public:
    Parallelogram(double a, double b, double A, double B)
        : Quadrangle(a, b, a, b, A, B, A, B) {}

    void print_info() const override {
        std::cout << "Параллелограмм:\n";
        Quadrangle::print_info();
    }

    bool check() const override {
        return Quadrangle::check() && a == c && b == d && A == C && B == D;
    }
};

// Класс Rhombus для ромбов
class Rhombus : public Quadrangle {
public:
    Rhombus(double a, double A, double B)
        : Quadrangle(a, a, a, a, A, B, A, B) {}

    void print_info() const override {
        std::cout << "Ромб:\n";
        Quadrangle::print_info();
    }

    bool check() const override {
        return Quadrangle::check() && a == b && b == c && c == d && A == C && B == D;
    }
};

// Функция для вывода информации о фигуре и проверки её правильности
void print_info(const Figure* figure) {
    figure->print_info();
    if (figure->check()) {
        std::cout << "Правильная\n";
    } else {
        std::cout << "Неправильная\n";
    }
    std::cout << "\n";
}

int main() {
    // Создание объектов каждой фигуры
    Figure fig(0);
    Triangle triangle(10, 20, 30, 50, 60, 70);
    RightTriangle rightTriangle(10, 20, 30, 50, 60);
    IsoscelesTriangle isoscelesTriangle(10, 20, 50, 60);
    EquilateralTriangle equilateralTriangle(30);

    Quadrangle quadrangle(10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle rectangle(10, 20);
    Square square(20);
    Parallelogram parallelogram(20, 30, 30, 40);
    Rhombus rhombus(30, 30, 40);

    // Вывод информации о каждой фигуре и проверка правильности
    print_info(&fig);
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
