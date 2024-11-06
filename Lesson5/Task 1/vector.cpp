#include <iostream>
#include <vector>
#include <algorithm>

// Функция для удаления всех дубликатов из вектора
void removeDuplicates(std::vector<int>& vec) {
    // Сначала сортируем вектор
    std::sort(vec.begin(), vec.end());
    
    // Используем std::unique для перемещения дубликатов в конец
    auto lastUnique = std::unique(vec.begin(), vec.end());
    
    // Удаляем все элементы после уникальных
    vec.erase(lastUnique, vec.end());
}

int main() {
    std::vector<int> vec = {1, 1, 2, 5, 6, 1, 2, 4};

    std::cout << "[IN]: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Удаляем дубликаты
    removeDuplicates(vec);

    std::cout << "[OUT]: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
