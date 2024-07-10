#include <iostream>
#include "counter.h"

int main() {
    std::string response;
    int initial_value;
    char command;
    Counter counter;

    std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
    std::cin >> response;

    if (response == "да") {
        std::cout << "Введите начальное значение счётчика: ";
        std::cin >> initial_value;
        counter = Counter(initial_value);
    } else {
        counter = Counter();
    }

    do {
        std::cout << "Введите команду ('+', '-', '=' или 'x'): ";
        std::cin >> command;

        switch (command) {
            case '+':
                counter.increment();
                break;
            case '-':
                counter.decrement();
                break;
            case '=':
                std::cout << counter.getValue() << std::endl;
                break;
            case 'x':
                std::cout << "До свидания!" << std::endl;
                break;
            default:
                std::cout << "Неверная команда" << std::endl;
                break;
        }
    } while (command != 'x');

    return 0;
}
