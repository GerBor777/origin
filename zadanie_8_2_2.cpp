#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <random>

std::mutex console_mutex; // Мьютекс для синхронизации вывода в консоль

// Цвета для терминала
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"

// Функция для отображения прогресса
void progressBar(int thread_num, int length, int speed) {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> error_chance(1, 10); // 10% вероятность ошибки

    std::string progress;
    for (int i = 0; i < length; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));

        // Симуляция ошибки
        if (error_chance(gen) == 1) {
            progress += RED "X" RESET; // Красный "X" вместо #
        } else {
            progress += GREEN "#" RESET; // Обычный прогресс #
        }

        // Блокируем мьютекс для синхронизации вывода
        {
            std::lock_guard<std::mutex> lock(console_mutex);
            std::cout << "Поток [" << thread_num << "] ID: " << std::this_thread::get_id() 
                      << " | " << progress << "\r" << std::flush;
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    // Выводим итоговое время работы потока
    {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cout << "\nПоток [" << thread_num << "] завершён за " << YELLOW << elapsed.count() 
                  << " сек" << RESET << std::endl;
    }
}

int main() {
    int num_threads = 5; // Количество потоков
    int bar_length = 20; // Длина прогресс-бара
    int speed = 200; // Скорость обновления (мс)

    std::vector<std::thread> threads;

    // Запускаем потоки
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(progressBar, i + 1, bar_length, speed);
    }

    // Дожидаемся завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "\nВсе потоки завершены!" << std::endl;
    return 0;
}
