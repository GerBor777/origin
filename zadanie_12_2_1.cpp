#include <iostream>
#include <fstream>
#include <memory>

// 🔹 Интерфейс форматирования
class Formatter {
public:
    virtual ~Formatter() = default;
    virtual std::string format(const std::string& data) const = 0;
};

// 🔹 Реализации форматирования
class TextFormatter : public Formatter {
public:
    std::string format(const std::string& data) const override {
        return data;
    }
};

class HTMLFormatter : public Formatter {
public:
    std::string format(const std::string& data) const override {
        return "<html>" + data + "</html>";
    }
};

class JSONFormatter : public Formatter {
public:
    std::string format(const std::string& data) const override {
        return "{ \"data\": \"" + data + "\" }";
    }
};

// 🔹 Класс данных (больше не зависит от форматов)
class Data {
public:
    explicit Data(std::string data) : data_(std::move(data)) {}

    const std::string& getData() const {
        return data_;
    }

private:
    std::string data_;
};

// 🔹 Класс для сохранения данных с заданным форматтером
class PrintableData {
public:
    PrintableData(std::shared_ptr<Data> data, std::shared_ptr<Formatter> formatter)
        : data_(std::move(data)), formatter_(std::move(formatter)) {}

    std::string print() const {
        return formatter_->format(data_->getData());
    }

private:
    std::shared_ptr<Data> data_;
    std::shared_ptr<Formatter> formatter_;
};

// 🔹 Функция сохранения в файл
void saveTo(std::ofstream &file, const PrintableData& printable) {
    file << printable.print();
}

int main() {
    auto data = std::make_shared<Data>("Hello, SOLID!");

    // Используем разные форматы
    auto textPrintable = PrintableData(data, std::make_shared<TextFormatter>());
    auto htmlPrintable = PrintableData(data, std::make_shared<HTMLFormatter>());
    auto jsonPrintable = PrintableData(data, std::make_shared<JSONFormatter>());

    // Сохраняем в файлы
    std::ofstream textFile("text.txt");
    saveTo(textFile, textPrintable);

    std::ofstream htmlFile("data.html");
    saveTo(htmlFile, htmlPrintable);

    std::ofstream jsonFile("data.json");
    saveTo(jsonFile, jsonPrintable);

    // Вывод в консоль
    std::cout << "Text: " << textPrintable.print() << "\n";
    std::cout << "HTML: " << htmlPrintable.print() << "\n";
    std::cout << "JSON: " << jsonPrintable.print() << "\n";

    return 0;
}
