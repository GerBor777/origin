#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    // Вводим текст
    std::string text;
    std::cout << "[IN]: ";
    std::getline(std::cin, text);

    // Считаем частоту каждого символа
    std::map<char, int> frequency;
    for (char c : text) {
        frequency[c]++;
    }

    // Копируем элементы map в вектор для сортировки
    std::vector<std::pair<char, int>> freq_vec(frequency.begin(), frequency.end());

    // Сортируем вектор по убыванию частоты
    std::sort(freq_vec.begin(), freq_vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Выводим результат
    std::cout << "[OUT]:\n";
    for (const auto& [ch, freq] : freq_vec) {
        std::cout << ch << ": " << freq << '\n';
    }

    return 0;
}
