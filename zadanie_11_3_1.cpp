#include <iostream>
#include <fstream>
#include <memory>
#include <exception>

// Перечисление типов сообщений
enum class LogType {
    Warning,
    Error,
    FatalError,
    Unknown
};

// Класс сообщения о логировании
class LogMessage {
private:
    LogType logType;
    std::string logText;
public:
    LogMessage(LogType type, const std::string& message) : logType(type), logText(message) {}

    LogType type() const { return logType; }
    const std::string& message() const { return logText; }
};

// Базовый класс обработчика
class LogHandler {
protected:
    std::unique_ptr<LogHandler> nextHandler;  // Следующий обработчик в цепочке
public:
    virtual ~LogHandler() = default;

    // Устанавливаем следующий обработчик
    void setNext(std::unique_ptr<LogHandler> next) {
        nextHandler = std::move(next);
    }

    // Базовый метод обработки
    virtual void handle(const LogMessage& msg) {
        if (nextHandler) {
            nextHandler->handle(msg);
        } else {
            throw std::runtime_error("Unhandled log message: " + msg.message());
        }
    }
};

// Обработчик фатальных ошибок (FatalError)
class FatalErrorHandler : public LogHandler {
public:
    void handle(const LogMessage& msg) override {
        if (msg.type() == LogType::FatalError) {
            throw std::runtime_error("[FATAL ERROR] " + msg.message());
        }
        LogHandler::handle(msg);
    }
};

// Обработчик ошибок (Error) — записывает в файл
class ErrorHandler : public LogHandler {
private:
    std::string filename;
public:
    explicit ErrorHandler(const std::string& file) : filename(file) {}

    void handle(const LogMessage& msg) override {
        if (msg.type() == LogType::Error) {
            std::ofstream outFile(filename, std::ios::app);
            if (outFile.is_open()) {
                outFile << "[ERROR] " << msg.message() << std::endl;
            }
            outFile.close();
        } else {
            LogHandler::handle(msg);
        }
    }
};

// Обработчик предупреждений (Warning) — выводит в консоль
class WarningHandler : public LogHandler {
public:
    void handle(const LogMessage& msg) override {
        if (msg.type() == LogType::Warning) {
            std::cout << "[WARNING] " << msg.message() << std::endl;
        } else {
            LogHandler::handle(msg);
        }
    }
};

// Обработчик неизвестных сообщений (Unknown)
class UnknownHandler : public LogHandler {
public:
    void handle(const LogMessage& msg) override {
        if (msg.type() == LogType::Unknown) {
            throw std::runtime_error("[UNKNOWN MESSAGE] " + msg.message());
        }
        LogHandler::handle(msg);
    }
};

// Тестирование цепочки ответственности
int main() {
    try {
        // Создаём цепочку обработчиков
        auto fatalHandler = std::make_unique<FatalErrorHandler>();
        auto errorHandler = std::make_unique<ErrorHandler>("log.txt");
        auto warningHandler = std::make_unique<WarningHandler>();
        auto unknownHandler = std::make_unique<UnknownHandler>();

        // Устанавливаем цепочку
        fatalHandler->setNext(std::move(errorHandler));
        fatalHandler->nextHandler->setNext(std::move(warningHandler));
        fatalHandler->nextHandler->nextHandler->setNext(std::move(unknownHandler));

        // Обработчик верхнего уровня
        LogHandler* handlerChain = fatalHandler.get();

        // Логируем разные сообщения
        handlerChain->handle(LogMessage(LogType::Warning, "Используется устаревший API."));
        handlerChain->handle(LogMessage(LogType::Error, "Ошибка соединения с сервером."));
        handlerChain->handle(LogMessage(LogType::FatalError, "Фатальный сбой системы!"));

        // Неизвестный тип (вызовет исключение)
        handlerChain->handle(LogMessage(LogType::Unknown, "Какое-то странное сообщение."));
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception caught: " << ex.what() << std::endl;
    }

    return 0;
}
