#include <iostream>
#include <vector>

template <typename T>
class Table {
public:
    // Конструктор, инициализирующий таблицу с заданными размерами
    Table(int rows, int cols) : data(rows, std::vector<T>(cols)) {}

    // Неконстантная версия оператора []
    std::vector<T>& operator[](int index) {
        return data[index];
    }

    // Константная версия оператора []
    const std::vector<T>& operator[](int index) const {
        return data[index];
    }

    // Константная функция, возвращающая размер таблицы
    std::pair<int, int> Size() const {
        return {data.size(), data[0].size()};
    }

private:
    std::vector<std::vector<T>> data;
};

int main() {
    // Создаём таблицу размера 2x3
    Table<int> test(2, 3);

    // Пример записи и вывода значений
    test[0][0] = 4;
    std::cout << test[0][0] << std::endl; // выводит 4

    // Проверка функции размера таблицы
    auto size = test.Size();
    std::cout << "Rows: " << size.first << ", Cols: " << size.second << std::endl; // выводит "Rows: 2, Cols: 3"

    return 0;
}
