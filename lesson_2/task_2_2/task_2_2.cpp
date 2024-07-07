#include <iostream>
#include <string>

class Counter {
private:
    int value;

public:
    // Constructor with default value
    Counter(int initialValue = 1) : value(initialValue) {}

    // Method to increase the counter by 1
    void increment() {
        value++;
    }

    // Method to decrease the counter by 1
    void decrement() {
        value--;
    }

    // Method to get the current value of the counter
    int getValue() const {
        return value;
    }
};

int main() {
    int initialValue;
    std::string userInput;
    std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
    std::cin >> userInput;

    if (userInput == "да" || userInput == "Да") {
        std::cout << "Введите начальное значение счётчика: ";
        std::cin >> initialValue;
    } else {
        initialValue = 1;
    }

    Counter counter(initialValue);

    while (true) {
        std::cout << "Введите команду ('+', '-', '=' или 'x'): ";
        std::cin >> userInput;

        if (userInput == "+") {
            counter.increment();
        } else if (userInput == "-") {
            counter.decrement();
        } else if (userInput == "=") {
            std::cout << counter.getValue() << std::endl;
        } else if (userInput == "x") {
            std::cout << "До свидания!" << std::endl;
            break;
        } else {
            std::cout << "Неверная команда. Попробуйте ещё раз." << std::endl;
        }
    }

    return 0;
}
