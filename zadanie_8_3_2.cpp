#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

// Глубина рекурсии (размер блока, после которого работаем синхронно)
const size_t MIN_BLOCK_SIZE = 4;

// Параллельная версия std::for_each
template<typename Iterator, typename Func>
void parallel_for_each(Iterator begin, Iterator end, Func func) {
    size_t length = std::distance(begin, end);

    // Если блок маленький, выполняем синхронно
    if (length <= MIN_BLOCK_SIZE) {
        std::for_each(begin, end, func);
        return;
    }

    // Делим массив на 2 части
    Iterator mid = begin + length / 2;

    // Запускаем асинхронную задачу на первой половине
    auto future = std::async(std::launch::async, parallel_for_each<Iterator, Func>, begin, mid, func);

    // Рекурсивно обрабатываем вторую половину (в текущем потоке)
    parallel_for_each(mid, end, func);

    // Ждем завершения первой половины
    future.get();
}

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Исходный массив: ";
    for (int num : data) std::cout << num << " ";
    std::cout << std::endl;

    // Применяем for_each параллельно
    parallel_for_each(data.begin(), data.end(), [](int& x) {
        x *= 2;  // Умножаем каждый элемент на 2
    });

    std::cout << "Результат: ";
    for (int num : data) std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}
