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

    // Конструктор копирования
    smart_array(const smart_array& other) : capacity(other.capacity), size(other.size) {
        data = new int[capacity];  // Выделяем память для нового массива
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];  // Копируем элементы
        }
    }

    // Оператор присваивания
    smart_array& operator=(const smart_array& other) {
        if (this == &other) {
            return *this;  // Защита от самоприсваивания
        }

        // Освобождаем старую память
        delete[] data;

        // Копируем данные
        capacity = other.capacity;
        size = other.size;
        data = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }

        return *this;
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
        smart_array arr(5);  // Создаем массив на 5 элементов
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);  // Создаем еще один массив на 2 элемента
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;  // Присваиваем один массив другому

        // Проверка элементов
        std::cout << arr.get_element(0) << std::endl;  // Ожидается вывод: 44
        std::cout << arr.get_element(1) << std::endl;  // Ожидается вывод: 34
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;  // Обработка исключений
    }

    return 0;
}
