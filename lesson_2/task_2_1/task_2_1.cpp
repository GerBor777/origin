#include <iostream>

class Calculator {
private:
    double num1;
    double num2;

public:
    // Constructor to initialize numbers
    Calculator(double n1 = 0, double n2 = 0) : num1(n1), num2(n2) {}

    // Method to set num1
    bool set_num1(double n1) {
        if (n1 != 0) {
            num1 = n1;
            return true;
        }
        return false;
    }

    // Method to set num2
    bool set_num2(double n2) {
        if (n2 != 0) {
            num2 = n2;
            return true;
        }
        return false;
    }

    // Method to add num1 and num2
    double add() {
        return num1 + num2;
    }

    // Method to multiply num1 and num2
    double multiply() {
        return num1 * num2;
    }

    // Method to subtract num2 from num1
    double subtract_1_2() {
        return num1 - num2;
    }

    // Method to subtract num1 from num2
    double subtract_2_1() {
        return num2 - num1;
    }

    // Method to divide num1 by num2
    double divide_1_2() {
        return num1 / num2;
    }

    // Method to divide num2 by num1
    double divide_2_1() {
        return num2 / num1;
    }
};

int main() {
    Calculator calc;
    double n1, n2;
    while (true) {
        std::cout << "Введите первое число: ";
        std::cin >> n1;
        std::cout << "Введите второе число: ";
        std::cin >> n2;

        if (calc.set_num1(n1) && calc.set_num2(n2)) {
            std::cout << "Результаты операций:" << std::endl;
            std::cout << "Сложение: " << calc.add() << std::endl;
            std::cout << "Умножение: " << calc.multiply() << std::endl;
            std::cout << "Вычитание (первое - второе): " << calc.subtract_1_2() << std::endl;
            std::cout << "Вычитание (второе - первое): " << calc.subtract_2_1() << std::endl;
            std::cout << "Деление (первое / второе): " << calc.divide_1_2() << std::endl;
            std::cout << "Деление (второе / первое): " << calc.divide_2_1() << std::endl;
        } else {
            std::cout << "Число не должно быть равно 0. Попробуйте ещё раз." << std::endl;
        }
    }
    return 0;
}
