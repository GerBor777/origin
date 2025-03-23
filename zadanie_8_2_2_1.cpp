#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <random>

std::mutex console_mutex; // Мьютекс для синхронизации вывода

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CLEAR_SCREEN "\033[2J\033[H"  // Очистка экрана

std::vector<std::string> progressBars; // Хранит текущий прогресс каждого потока
bool running = true; // Флаг работы потоков

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
            progress += RED "X" RESET; // Красный "X"
        } else {
            progress += GREEN "#" RESET; // Обычный прогресс
        }

        // Обновляем строку прогресса
        {
            std::lock_guard<std::mutex> lock(console_mutex);
            progressBars[thread_num] = "Поток [" + std::to_string(thread_num + 1) + "] " + progress;
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    // Выводим итоговое сообщение
    {
        std::lock_guard<std::mutex> lock(console_mutex);
        progressBars[thread_num] += " | Завершён за " + std::to_string(elapsed.count()) + " сек";
    }
}

void displayProgress(int num_threads) {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Частота обновления экрана
        {
            std::lock_guard<std::mutex> lock(console_mutex);
            std::cout << CLEAR_SCREEN; // Очистка экрана перед выводом
            for (const auto &bar : progressBars) {
                std::cout << bar << std::endl;
            }
        }
    }
}

int main() {
    int num_threads = 5;
    int bar_length = 20;
    int speed = 200;

    progressBars.resize(num_threads, ""); // Инициализация пустыми строками
    std::vector<std::thread> threads;
    
    // Запуск потока, который обновляет консоль
    std::thread display_thread(displayProgress, num_threads);

    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(progressBar, i, bar_length, speed);
    }

    for (auto &t : threads) {
        t.join();
    }

    running = false; // Останавливаем поток отрисовки
    display_thread.join();

    std::cout << "\nВсе потоки завершены!" << std::endl;
    return 0;
}
