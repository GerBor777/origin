#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>

// Базовый интерфейс наблюдателя
class Observer {
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

// Класс, за которым следят наблюдатели
class LogSubject {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void warning(const std::string& message) const {
        for (auto observer : observers) {
            if (observer) observer->onWarning(message);
        }
    }

    void error(const std::string& message) const {
        for (auto observer : observers) {
            if (observer) observer->onError(message);
        }
    }

    void fatalError(const std::string& message) const {
        for (auto observer : observers) {
            if (observer) observer->onFatalError(message);
        }
    }
};

// Наблюдатель: логирование предупреждений в консоль
class ConsoleWarningObserver : public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << "[WARNING] " << message << std::endl;
    }
};

// Наблюдатель: логирование ошибок в файл
class FileErrorObserver : public Observer {
private:
    std::string filename;
public:
    explicit FileErrorObserver(const std::string& file) : filename(file) {}

    void onError(const std::string& message) override {
        std::ofstream outFile(filename, std::ios::app);
        if (outFile.is_open()) {
            outFile << "[ERROR] " << message << std::endl;
        }
        outFile.close();
    }
};

// Наблюдатель: логирование фатальных ошибок в консоль и в файл
class ConsoleAndFileFatalErrorObserver : public Observer {
private:
    std::string filename;
public:
    explicit ConsoleAndFileFatalErrorObserver(const std::string& file) : filename(file) {}

    void onFatalError(const std::string& message) override {
        std::cout << "[FATAL ERROR] " << message << std::endl;

        std::ofstream outFile(filename, std::ios::app);
        if (outFile.is_open()) {
            outFile << "[FATAL ERROR] " << message << std::endl;
        }
        outFile.close();
    }
};

// Тестирование
int main() {
    LogSubject logger;

    ConsoleWarningObserver consoleWarning;
    FileErrorObserver fileError("log.txt");
    ConsoleAndFileFatalErrorObserver fatalErrorObserver("log.txt");

    logger.addObserver(&consoleWarning);
    logger.addObserver(&fileError);
    logger.addObserver(&fatalErrorObserver);

    logger.warning("Это предупреждение.");
    logger.error("Произошла ошибка.");
    logger.fatalError("Критическая ошибка!");

    logger.removeObserver(&fileError);  // Удаляем наблюдателя

    return 0;
}
