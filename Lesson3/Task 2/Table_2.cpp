#include <iostream>
#include <stdexcept>

template <class T>
class RowProxy {
public:
    // Конструктор прокси, принимающий указатель на строку
    RowProxy(T* rowptr) : rowptr(rowptr) {}

    // Оператор доступа к элементу строки
    T& operator[](size_t index) {
        if (!rowptr) throw std::runtime_error("Row pointer is null");
        return rowptr[index];
    }

private:
    T* rowptr;
};

template <class T>
class Table {
public:
    // Конструктор, инициализирующий таблицу с заданными размерами
    Table(size_t rows, size_t cols) : rows(rows), cols(cols) {
        data = new T*[rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols]{};
        }
    }

    // Деструктор, освобождающий память
    ~Table() {
        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Оператор доступа к строке через прокси
    RowProxy<T> operator[](size_t row) {
        if (row >= rows) throw std::out_of_range("Row index out of range");
        return RowProxy<T>(data[row]);
    }

    // Константная версия оператора доступа к строке
    const RowProxy<T> operator[](size_t row) const {
        if (row >= rows) throw std::out_of_range("Row index out of range");
        return RowProxy<T>(data[row]);
    }

    // Функция, возвращающая размер таблицы
    std::pair<size_t, size_t> Size() const {
        return {rows, cols};
    }

    // Запрещаем копирование
    Table(const Table&) = delete;
    Table& operator=(const Table&) = delete;

private:
    T** data;
    size_t rows;
    size_t cols;
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
