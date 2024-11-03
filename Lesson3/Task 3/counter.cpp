#include <iostream>
#include <vector>
#include <algorithm>

class DivisibleByThreeCounter {
private:
    int sum;
    int count;

public:
    DivisibleByThreeCounter() : sum(0), count(0) {}

    // Оператор () для проверки и накопления данных
    void operator()(int number) {
        if (number % 3 == 0) {
            sum += number;
            count++;
        }
    }

    // Метод для получения суммы чисел, делящихся на 3
    int get_sum() const {
        return sum;
    }

    // Метод для получения количества чисел, делящихся на 3
    int get_count() const {
        return count;
    }
};

int main() {
    std::vector<int> numbers = {4, 1, 3, 6, 25, 54};

    // Создаём экземпляр функтора
    DivisibleByThreeCounter counter;

    // Используем std::for_each для подсчёта
    std::for_each(numbers.begin(), numbers.end(), counter);

    // Выводим результаты
    std::cout << "[OUT]: get_sum() = " << counter.get_sum() << std::endl;
    std::cout << "[OUT]: get_count() = " << counter.get_count() << std::endl;

    return 0;
}
