#include <iostream>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

namespace dbo = Wt::Dbo;

// Определение моделей
class Publisher;
class Book;
class Shop;
class Stock;
class Sale;

class Publisher {
public:
    dbo::collection<dbo::ptr<Book>> books;
    std::string name;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, name, "name");
        dbo::hasMany(a, books, dbo::ManyToOne, "publisher");
    }
};

class Book {
public:
    dbo::ptr<Publisher> publisher;
    dbo::collection<dbo::ptr<Stock>> stocks;
    std::string title;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, title, "title");
        dbo::belongsTo(a, publisher, "publisher");
        dbo::hasMany(a, stocks, dbo::ManyToOne, "book");
    }
};

class Shop {
public:
    dbo::collection<dbo::ptr<Stock>> stocks;
    std::string name;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, name, "name");
        dbo::hasMany(a, stocks, dbo::ManyToOne, "shop");
    }
};

class Stock {
public:
    dbo::ptr<Book> book;
    dbo::ptr<Shop> shop;
    int count;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, count, "count");
        dbo::belongsTo(a, book, "book");
        dbo::belongsTo(a, shop, "shop");
    }
};

class Sale {
public:
    dbo::ptr<Stock> stock;
    double price;
    std::string date_sale;
    int count;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, price, "price");
        dbo::field(a, date_sale, "date_sale");
        dbo::field(a, count, "count");
        dbo::belongsTo(a, stock, "stock");
    }
};

void createSchema(dbo::Session& session) {
    session.createTables();
    std::cout << "Таблицы созданы!" << std::endl;
}

void insertTestData(dbo::Session& session) {
    dbo::Transaction transaction(session);

    // Добавляем издателей
    auto publisher1 = session.add(new Publisher{"Penguin"});
    auto publisher2 = session.add(new Publisher{"HarperCollins"});

    // Добавляем книги
    auto book1 = session.add(new Book{"Book A", publisher1});
    auto book2 = session.add(new Book{"Book B", publisher1});
    auto book3 = session.add(new Book{"Book C", publisher2});

    // Добавляем магазины
    auto shop1 = session.add(new Shop{"BookStore1"});
    auto shop2 = session.add(new Shop{"BookStore2"});

    // Добавляем складские записи
    session.add(new Stock{book1, shop1, 10});
    session.add(new Stock{book2, shop2, 5});
    session.add(new Stock{book3, shop1, 8});

    transaction.commit();
    std::cout << "Тестовые данные добавлены!" << std::endl;
}

void findShopsSellingPublisher(dbo::Session& session, const std::string& publisherName) {
    dbo::Transaction transaction(session);

    // Находим издателя
    dbo::ptr<Publisher> publisher = session.find<Publisher>().where("name = ?").bind(publisherName);

    if (!publisher) {
        std::cout << "Издатель не найден!" << std::endl;
        return;
    }

    std::cout << "Магазины, продающие книги издателя " << publisherName << ":" << std::endl;

    // Находим магазины через книги и складские записи
    for (const auto& book : publisher->books) {
        for (const auto& stock : book->stocks) {
            std::cout << "- " << stock->shop->name << std::endl;
        }
    }

    transaction.commit();
}

int main() {
    try {
        dbo::backend::Postgres postgres("host=localhost user=postgres password=postgres dbname=bookstore");
        dbo::Session session;
        session.setConnection(postgres);

        createSchema(session);
        insertTestData(session);

        std::cout << "Введите имя издателя: ";
        std::string publisherName;
        std::getline(std::cin, publisherName);

        findShopsSellingPublisher(session, publisherName);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
