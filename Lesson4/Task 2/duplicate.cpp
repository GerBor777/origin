#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

int main() {
    // Чтение количества элементов
    int n;
    std::cout << "[IN]:\n";
    std::cin >> n;

    // Чтение чисел и удаление дубликатов с помощью set
    std::set<int> unique_numbers;
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        unique_numbers.insert(num);
    }

    // Копируем элементы set в вектор для сортировки по убыванию
    std::vector<int> sorted_numbers(unique_numbers.rbegin(), unique_numbers.rend());

    // Выводим результат
    std::cout << "[OUT]:\n";
    for (int num : sorted_numbers) {
        std::cout << num << '\n';
    }

    return 0;
}
