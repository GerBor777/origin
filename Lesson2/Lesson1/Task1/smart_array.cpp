#include <iostream>
#include <stdexcept>

class smart_array {
private:
    int* data;            // Указатель на массив данных
    size_t capacity;       // Размер выделенной памяти (ёмкость массива)
    size_t size;           // Текущий размер массива (количество добавленных элементов)

public:
    // Конструктор
    smart_array(size_t capacity) : capacity(capacity), size(0) {
        if (capacity == 0) {
            throw std::invalid_argument("Array size must be greater than 0.");
        }
        data = new int[capacity];  // Выделение памяти для массива
    }

    // Метод добавления элемента в массив
    void add_element(int element) {
        if (size >= capacity) {
            throw std::out_of_range("Array capacity exceeded.");
        }
        data[size++] = element;  // Добавление элемента и увеличение размера массива
    }

    // Метод получения элемента по индексу
    int get_element(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index is out of range.");
        }
        return data[index];  // Возврат элемента по индексу
    }

    // Деструктор
    ~smart_array() {
        delete[] data;  // Освобождение выделенной памяти
    }
};

int main() {
    try {
        smart_array arr(5);  // Создаем умный массив с размером 5
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);

        std::cout << arr.get_element(1) << std::endl;  // Ожидается вывод: 4
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;  // Обработка исключений
    }

    return 0;
}
