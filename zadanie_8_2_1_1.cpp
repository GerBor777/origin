#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <mutex>

std::atomic<int> client_count(0);  // Атомарный счётчик клиентов
const int MAX_CLIENTS = 10;        // Максимальное количество клиентов
std::mutex cout_mutex;             // Мьютекс для синхронизации вывода

void add_clients() {
    while (true) {
        int current = client_count.load(std::memory_order_acquire);
        if (current < MAX_CLIENTS) {
            client_count.fetch_add(1, std::memory_order_acq_rel);

            // Блокируем вывод в консоль, чтобы избежать перемешивания
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "[+] Клиент добавлен. Всего: " << client_count.load(std::memory_order_acquire) << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void serve_clients() {
    while (true) {
        int current = client_count.load(std::memory_order_acquire);
        if (current > 0) {
            client_count.fetch_sub(1, std::memory_order_acq_rel);

            // Блокируем вывод в консоль, чтобы избежать перемешивания
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "[-] Клиент обслужен. Осталось: " << client_count.load(std::memory_order_acquire) << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main() {
    std::thread producer(add_clients);
    std::thread consumer(serve_clients);

    producer.join();
    consumer.join();

    return 0;
}
