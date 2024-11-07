#include <iostream>
#include <stdexcept>

template <typename T>
class MyVector {
public:
    // Конструктор по умолчанию
    MyVector() : data(nullptr), vec_size(0), vec_capacity(0) {}

    // Деструктор
    ~MyVector() {
        delete[] data;
    }

    // Доступ к элементу по индексу с проверкой
    T& at(int index) {
        if (index < 0 || index >= vec_size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Добавление элемента в конец
    void push_back(const T& value) {
        if (vec_size == vec_capacity) {
            resize();
        }
        data[vec_size++] = value;
    }

    // Получение размера контейнера
    int size() const {
        return vec_size;
    }

    // Получение вместимости контейнера
    int capacity() const {
        return vec_capacity;
    }

private:
    T* data;           // Указатель на массив данных
    int vec_size;      // Текущее количество элементов
    int vec_capacity;  // Текущая ёмкость

    // Увеличение ёмкости вектора
    void resize() {
        vec_capacity = (vec_capacity == 0) ? 1 : vec_capacity * 2;
        T* new_data = new T[vec_capacity];

        // Копируем старые данные в новый массив
        for (int i = 0; i < vec_size; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;  // Освобождаем старую память
        data = new_data;  // Перенаправляем data на новый массив
    }
};

int main() {
    MyVector<int> vec;

    // Добавляем элементы
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // Проверка методов
    std::cout << "Element at index 1: " << vec.at(1) << std::endl;
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;

    return 0;
}
