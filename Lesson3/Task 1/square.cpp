#include <iostream>
#include <vector>

// Шаблонная функция для чисел
template <typename T>
T square(const T& value) {
    return value * value;
}

// Специализация шаблонной функции для вектора
template <typename T>
std::vector<T> square(const std::vector<T>& vec) {
    std::vector<T> result;
    result.reserve(vec.size());
    for (const auto& elem : vec) {
        result.push_back(elem * elem);
    }
    return result;
}

// Функция для вывода результатов
template <typename T>
void print(const T& value) {
    std::cout << value << std::endl;
}

// Специализация функции вывода для вектора
template <typename T>
void print(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Пример возведения числа в квадрат
    int num = 4;
    std::cout << "[IN]: " << num << std::endl;
    std::cout << "[OUT]: ";
    print(square(num));

    // Пример возведения элементов вектора в квадрат
    std::vector<int> vec = {-1, 4, 8};
    std::cout << "[IN]: ";
    print(vec);
    std::cout << "[OUT]: ";
    print(square(vec));

    return 0;
}
