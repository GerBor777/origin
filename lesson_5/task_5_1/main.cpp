#include <iostream>
#include "math_functions.h"

int main() {
    double num1, num2;
    int operation;

    std::cout << "Введите первое число: ";
    std::cin >> num1;

    std::cout << "Введите второе число: ";
    std::cin >> num2;

    std::cout << "Выберите операцию (1 - сложение, 2 - вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
    std::cin >> operation;

    try {
        switch (operation) {
            case 1:
                std::cout << num1 << " + " << num2 << " = " << add(num1, num2) << std::endl;
                break;
            case 2:
                std::cout << num1 << " - " << num2 << " = " << subtract(num1, num2) << std::endl;
                break;
            case 3:
                std::cout << num1 << " * " << num2 << " = " << multiply(num1, num2) << std::endl;
                break;
            case 4:
                std::cout << num1 << " / " << num2 << " = " << divide(num1, num2) << std::endl;
                break;
            case 5:
                std::cout << num1 << " в степени " << num2 << " = " << power(num1, num2) << std::endl;
                break;
            default:
                std::cout << "Неверный выбор операции" << std::endl;
                break;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
