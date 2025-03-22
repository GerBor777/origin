#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

// Абстрактный класс "Фигура"
class Shape {
public:
    virtual void move(double dx, double dy, double dz = 0) = 0;
    virtual void scale(double sx, double sy, double sz = 1) = 0;
    virtual void print() const = 0;
    virtual ~Shape() = default;
};

// Линия
class Line : public Shape {
private:
    double x1, y1, x2, y2;
public:
    Line(double x1, double y1, double x2, double y2) 
        : x1(x1), y1(y1), x2(x2), y2(y2) {}

    void move(double dx, double dy, double dz = 0) override {
        x1 += dx; y1 += dy;
        x2 += dx; y2 += dy;
    }

    void scale(double sx, double sy, double sz = 1) override {
        x1 *= sx; y1 *= sy;
        x2 *= sx; y2 *= sy;
    }

    void print() const override {
        std::cout << "Линия: (" << x1 << ", " << y1 << ") -> (" << x2 << ", " << y2 << ")\n";
    }
};

// Прямоугольник
class Rectangle : public Shape {
private:
    double x, y, width, height;
public:
    Rectangle(double x, double y, double width, double height)
        : x(x), y(y), width(width), height(height) {}

    void move(double dx, double dy, double dz = 0) override {
        x += dx;
        y += dy;
    }

    void scale(double sx, double sy, double sz = 1) override {
        width *= sx;
        height *= sy;
    }

    void print() const override {
        std::cout << "Прямоугольник: (" << x << ", " << y << "), W=" << width << ", H=" << height << "\n";
    }
};

// Окружность
class Circle : public Shape {
private:
    double x, y, radius;
public:
    Circle(double x, double y, double radius) : x(x), y(y), radius(radius) {}

    void move(double dx, double dy, double dz = 0) override {
        x += dx;
        y += dy;
    }

    void scale(double sx, double sy, double sz = 1) override {
        radius *= (sx + sy) / 2; // Окружность масштабируется одинаково по осям
    }

    void print() const override {
        std::cout << "Окружность: центр=(" << x << ", " << y << "), R=" << radius << "\n";
    }
};

// Параллелепипед
class Parallelepiped : public Shape {
private:
    double x, y, z, width, height, depth;
public:
    Parallelepiped(double x, double y, double z, double width, double height, double depth)
        : x(x), y(y), z(z), width(width), height(height), depth(depth) {}

    void move(double dx, double dy, double dz = 0) override {
        x += dx;
        y += dy;
        z += dz;
    }

    void scale(double sx, double sy, double sz) override {
        width *= sx;
        height *= sy;
        depth *= sz;
    }

    void print() const override {
        std::cout << "Параллелепипед: (" << x << ", " << y << ", " << z << "), W=" << width << ", H=" << height << ", D=" << depth << "\n";
    }
};

// Фабрика фигур
class ShapeFactory {
public:
    static std::shared_ptr<Shape> createRectangle(double x, double y, double width, double height) {
        return std::make_shared<Rectangle>(x, y, width, height);
    }

    static std::shared_ptr<Shape> createCircle(double x, double y, double radius) {
        return std::make_shared<Circle>(x, y, radius);
    }

    static std::shared_ptr<Shape> createLine(double x1, double y1, double x2, double y2) {
        return std::make_shared<Line>(x1, y1, x2, y2);
    }

    static std::shared_ptr<Shape> createParallelepiped(double x, double y, double z, double w, double h, double d) {
        return std::make_shared<Parallelepiped>(x, y, z, w, h, d);
    }
};

// Тестирование
int main() {
    std::vector<std::shared_ptr<Shape>> shapes;

    shapes.push_back(ShapeFactory::createRectangle(0, 0, 10, 5));
    shapes.push_back(ShapeFactory::createCircle(5, 5, 3));
    shapes.push_back(ShapeFactory::createLine(1, 1, 4, 4));
    shapes.push_back(ShapeFactory::createParallelepiped(0, 0, 0, 4, 5, 6));

    std::cout << "Исходные фигуры:\n";
    for (const auto& shape : shapes) {
        shape->print();
    }

    std::cout << "\nПеремещаем и масштабируем фигуры...\n";
    for (auto& shape : shapes) {
        shape->move(2, 2, 2);
        shape->scale(1.5, 1.5, 1.5);
        shape->print();
    }

    return 0;
}
