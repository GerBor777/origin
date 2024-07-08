#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Класс Address для хранения информации об адресе
class Address {
private:
    std::string city;
    std::string street;
    std::string houseNumber;
    std::string apartmentNumber;

public:
    Address(const std::string& city, const std::string& street, const std::string& houseNumber, const std::string& apartmentNumber)
        : city(city), street(street), houseNumber(houseNumber), apartmentNumber(apartmentNumber) {}

    std::string getCity() const {
        return city;
    }

    std::string toString() const {
        return city + ", " + street + ", " + houseNumber + ", " + apartmentNumber;
    }
};

// Класс AddressBook для управления коллекцией адресов
class AddressBook {
private:
    std::vector<Address> addresses;

public:
    void readFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Не удалось открыть файл " << filename << std::endl;
            return;
        }

        int N;
        inputFile >> N;
        inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Пропустить оставшуюся часть строки

        for (int i = 0; i < N; ++i) {
            std::string city, street, houseNumber, apartmentNumber;
            std::getline(inputFile, city);
            std::getline(inputFile, street);
            std::getline(inputFile, houseNumber);
            std::getline(inputFile, apartmentNumber);
            addresses.emplace_back(city, street, houseNumber, apartmentNumber);
        }

        inputFile.close();
    }

    void sortAddresses() {
        std::sort(addresses.begin(), addresses.end(), [](const Address& a, const Address& b) {
            return a.getCity() < b.getCity();
        });
    }

    void writeToFile(const std::string& filename) const {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            std::cerr << "Не удалось открыть файл " << filename << std::endl;
            return;
        }

        outputFile << addresses.size() << std::endl;
        for (const auto& address : addresses) {
            outputFile << address.toString() << std::endl;
        }

        outputFile.close();
    }
};

int main() {
    AddressBook addressBook;
    addressBook.readFromFile("in.txt");
    addressBook.sortAddresses();
    addressBook.writeToFile("out.txt");

    std::cout << "Адреса успешно отсортированы и записаны в файл out.txt" << std::endl;
    return 0;
}