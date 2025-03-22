#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <chrono>

// Асинхронный поиск минимального элемента в подмассиве
std::future<int> async_find_min_index(std::vector<int>& arr, int start) {
    return std::async(std::launch::async, [&arr, start]() {
        int min_index = start;
        for (int i = start + 1; i < arr.size(); i++) {
            if (arr[i] < arr[min_index]) {
                min_index = i;
            }
        }
        return min_index;
    });
}

// Асинхронная сортировка выбором
void selection_sort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        // Запускаем асинхронный поиск минимального элемента
        std::future<int> future_min = async_find_min_index(arr, i);

        // Ждем результат
        int min_index = future_min.get();

        // Обмениваем элементы
        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
        }
    }
}

int main() {
    std::vector<int> arr = {64, 25, 12, 22, 11, 90, 55, 3, 17, 45};

    std::cout << "Исходный массив: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    
    selection_sort(arr); // Асинхронная сортировка
    
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "Отсортированный массив: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    std::cout << "Время выполнения: " << elapsed.count() << " секунд" << std::endl;

    return 0;
}
