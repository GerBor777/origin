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

// Базовый класс для чтения адресов
class AddressReader {
public:
    virtual std::vector<Address> readAddresses(const std::string& filename) = 0;
};

// Класс для чтения адресов из текстового файла
class FileAddressReader : public AddressReader {
public:
    std::vector<Address> readAddresses(const std::string& filename) override {
        std::ifstream inputFile(filename);
        std::vector<Address> addresses;

        if (!inputFile.is_open()) {
            std::cerr << "Не удалось открыть файл " << filename << std::endl;
            return addresses;
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
        return addresses;
    }
};

// Класс AddressBook для управления коллекцией адресов
class AddressBook {
private:
    std::vector<Address> addresses;

public:
    void loadAddresses(AddressReader& reader, const std::string& filename) {
        addresses = reader.readAddresses(filename);
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
    FileAddressReader fileReader;
    AddressBook addressBook;

    addressBook.loadAddresses(fileReader, "in.txt");
    addressBook.sortAddresses();
    addressBook.writeToFile("out.txt");

    std::cout << "Адреса успешно отсортированы и записаны в файл out.txt" << std::endl;
    return 0;
}