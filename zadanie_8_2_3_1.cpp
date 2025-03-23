#include <iostream>
#include <mutex>
#include <thread>

// Класс с данными и мьютексом
class Data {
public:
    int value;
    std::mutex mtx;

    Data(int v) : value(v) {}
};

// 1️⃣ Вариант с std::lock_guard + std::lock (Теперь защищен от deadlock!)
void swap_lock_guard(Data& a, Data& b) {
    std::lock(a.mtx, b.mtx); // Одновременный захват мьютексов

    // Используем adopt_lock, чтобы передать владение мьютексами lock_guard'ам
    std::lock_guard<std::mutex> lockA(a.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lockB(b.mtx, std::adopt_lock);

    std::swap(a.value, b.value);
}

// 2️⃣ Вариант с std::scoped_lock (C++17, автоматически защищает от deadlock)
void swap_scoped_lock(Data& a, Data& b) {
    std::scoped_lock lock(a.mtx, b.mtx); // Одновременный захват мьютексов
    std::swap(a.value, b.value);
}

// 3️⃣ Вариант с std::unique_lock (более гибкий, но сложнее)
void swap_unique_lock(Data& a, Data& b) {
    std::unique_lock<std::mutex> lockA(a.mtx, std::defer_lock);
    std::unique_lock<std::mutex> lockB(b.mtx, std::defer_lock);

    std::lock(lockA, lockB); // Захват мьютексов без deadlock

    std::swap(a.value, b.value);
}

// Функция для теста в многопоточной среде
void test_swap(void (*swap_function)(Data&, Data&), const std::string& name) {
    Data a(1), b(2);

    std::cout << "=== Тест " << name << " ===" << std::endl;
    std::cout << "До: a = " << a.value << ", b = " << b.value << std::endl;

    std::thread t1(swap_function, std::ref(a), std::ref(b));
    std::thread t2(swap_function, std::ref(a), std::ref(b));

    t1.join();
    t2.join();

    std::cout << "После: a = " << a.value << ", b = " << b.value << std::endl << std::endl;
}

int main() {
    test_swap(swap_lock_guard, "lock_guard (Теперь безопасно!)");
    test_swap(swap_scoped_lock, "scoped_lock (C++17, безопасно)");
    test_swap(swap_unique_lock, "unique_lock (безопасно)");

    return 0;
}
