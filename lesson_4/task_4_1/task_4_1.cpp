#include <iostream>
#include <string>

// Базовый класс Figure
class Figure {
private:
    int sides_count;
    std::string name;

protected:
    Figure(int sides_count, const std::string& name)
        : sides_count(sides_count), name(name) {}

public:
    int getSidesCount() const {
        return sides_count;
    }

    std::string getName() const {
        return name;
    }
};

// Класс Triangle, наследуемый от Figure
class Triangle : public Figure {
public:
    Triangle() : Figure(3, "Треугольник") {}
};

// Класс Quadrangle, наследуемый от Figure
class Quadrangle : public Figure {
public:
    Quadrangle() : Figure(4, "Четырёхугольник") {}
};

int main() {
    // Создание объектов каждого класса
    Figure unknownFigure(0, "Фигура");
    Triangle triangle;
    Quadrangle quadrangle;

    // Вывод количества сторон для каждой фигуры
    std::cout << unknownFigure.getName() << ": " << unknownFigure.getSidesCount() << std::endl;
    std::cout << triangle.getName() << ": " << triangle.getSidesCount() << std::endl;
    std::cout << quadrangle.getName() << ": " << quadrangle.getSidesCount() << std::endl;

    return 0;
}
