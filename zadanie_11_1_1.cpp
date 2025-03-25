#include <iostream>
#include <fstream>
#include <memory>

// Базовый класс команды логирования
class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

// Логирование в консоль
class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << "[Console] " << message << std::endl;
    }
};

// Логирование в файл
class FileLogCommand : public LogCommand {
private:
    std::string filename;
public:
    explicit FileLogCommand(const std::string& file) : filename(file) {}

    void print(const std::string& message) override {
        std::ofstream outFile(filename, std::ios::app);
        if (outFile.is_open()) {
            outFile << "[File] " << message << std::endl;
        }
        outFile.close();
    }
};

// Функция, выполняющая команду
void print(LogCommand& command, const std::string& message) {
    command.print(message);
}

// Тестирование
int main() {
    ConsoleLogCommand consoleLogger;
    FileLogCommand fileLogger("log.txt");

    print(consoleLogger, "Привет, мир!");
    print(fileLogger, "Запись в файл");

    return 0;
}
