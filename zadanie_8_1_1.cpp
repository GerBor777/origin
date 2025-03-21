#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<int> client_count(0);
const int max_clients = 10;

void client_thread() {
    while (client_count < max_clients) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        client_count++;
        std::cout << "Новый клиент пришел. Всего клиентов: " << client_count.load() << std::endl;
    }
}

void operator_thread() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (client_count > 0) {
            client_count--;
            std::cout << "Операционист обслужил клиента. Осталось клиентов: " << client_count.load() << std::endl;
        } else {
            break;
        }
    }
}

int main() {
    std::thread client(client_thread);
    std::thread oper(operator_thread);
    
    client.join();
    oper.join();
    
    std::cout << "Все клиенты обслужены." << std::endl;
    return 0;
}
