#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <string>

// Шаблонная функция для печати контейнера
template <typename Container>
void print_container(const Container& container) {
    auto it = container.begin();
    // Проверяем, что контейнер не пустой
    if (it != container.end()) {
        std::cout << *it;  // Печатаем первый элемент без запятой
        ++it;  // Переходим к следующему элементу
    }
    // Печатаем оставшиеся элементы с запятой перед каждым
    while (it != container.end()) {
        std::cout << ", " << *it;
        ++it;
    }
    std::cout << std::endl;  // Завершаем строку
}

int main() {
    // Пример с std::set
    std::set<std::string> test_set = {"one", "two", "three", "four"};
    std::cout << "std::set output: ";
    print_container(test_set);  // Результат: four one three two (порядок не гарантирован)

    // Пример с std::list
    std::list<std::string> test_list = {"one", "two", "three", "four"};
    std::cout << "std::list output: ";
    print_container(test_list);  // Результат: one, two, three, four

    // Пример с std::vector
    std::vector<std::string> test_vector = {"one", "two", "three", "four"};
    std::cout << "std::vector output: ";
    print_container(test_vector);  // Результат: one, two, three, four

    return 0;
}
