#include <iostream>
#include <string>

using namespace std;

// Определение структуры Address
struct Address {
    string city;
    string street;
    int houseNumber;
    int apartmentNumber;
    int postalCode;
};

// Функция для вывода структуры Address на консоль
void printAddress(const Address& address) {
    cout << "Город: " << address.city << endl;
    cout << "Улица: " << address.street << endl;
    cout << "Номер дома: " << address.houseNumber << endl;
    cout << "Номер квартиры: " << address.apartmentNumber << endl;
    cout << "Индекс: " << address.postalCode << endl;
    cout << endl;
}

int main() {
    // Создание экземпляров структуры Address
    Address address1 = {"Москва", "Арбат", 12, 8, 123456};
    Address address2 = {"Ижевск", "Пушкина", 59, 143, 953769};

    // Вывод адресов на консоль
    printAddress(address1);
    printAddress(address2);

    return 0;
}