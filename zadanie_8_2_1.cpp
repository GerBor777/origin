#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

std::atomic<int> client_count(0);  // Атомарный счётчик клиентов
const int MAX_CLIENTS = 10;  // Максимальное количество клиентов

void add_clients() {
    while (true) {
        if (client_count < MAX_CLIENTS) {
            client_count.fetch_add(1, std::memory_order_relaxed);
            std::cout << "[+] Клиент добавлен. Всего: " << client_count.load() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void serve_clients() {
    while (true) {
        if (client_count > 0) {
            client_count.fetch_sub(1, std::memory_order_relaxed);
            std::cout << "[-] Клиент обслужен. Осталось: " << client_count.load() << std::endl;
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
