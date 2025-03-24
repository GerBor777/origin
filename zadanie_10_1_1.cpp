#include <iostream>
#include <algorithm>  // Для std::reverse
#include <memory>     // Для std::unique_ptr

// Базовый интерфейс
class IText {
public:
    virtual ~IText() = default;
    virtual void render(const std::string& text) const = 0;
};

// Обычный текст
class Text : public IText {
public:
    void render(const std::string& text) const override {
        std::cout << text << std::endl;
    }
};

// Декоратор (базовый класс)
class TextDecorator : public IText {
protected:
    std::unique_ptr<IText> wrappee;
public:
    explicit TextDecorator(IText* text) : wrappee(text) {}
};

// Декоратор: абзац
class Paragraph : public TextDecorator {
public:
    using TextDecorator::TextDecorator;
    void render(const std::string& text) const override {
        std::cout << "<p>" << text << "</p>" << std::endl;
    }
};

// Декоратор: реверс текста
class Reversed : public TextDecorator {
public:
    using TextDecorator::TextDecorator;
    void render(const std::string& text) const override {
        std::string reversedText = text;
        std::reverse(reversedText.begin(), reversedText.end());
        wrappee->render(reversedText);
    }
};

// Декоратор: ссылка
class Link : public TextDecorator {
public:
    using TextDecorator::TextDecorator;
    void render(const std::string& url, const std::string& text) const {
        std::cout << "<a href=\"" << url << "\">" << text << "</a>" << std::endl;
    }
};

// Тестирование
int main() {
    std::unique_ptr<IText> simpleText = std::make_unique<Text>();
    
    std::unique_ptr<IText> paragraphText = std::make_unique<Paragraph>(new Text());
    paragraphText->render("Hello world"); // <p>Hello world</p>

    std::unique_ptr<IText> reversedText = std::make_unique<Reversed>(new Text());
    reversedText->render("Hello world");  // dlrow olleH

    // Link не является стандартным декоратором, поэтому используем отдельный вызов
    Link linkText(new Text());
    linkText.render("https://netology.ru", "Hello world"); 
    // <a href="https://netology.ru">Hello world</a>

    return 0;
}
