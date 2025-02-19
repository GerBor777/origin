#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <memory>

namespace dbo = Wt::Dbo;

// Класс издателя
class Publisher {
public:
    std::string name;
    
    dbo::collection< dbo::ptr<class Book> > books;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, name, "name");
        dbo::hasMany(a, books, dbo::ManyToOne, "publisher");
    }
};

// Класс книги
class Book {
public:
    std::string title;
    dbo::ptr<Publisher> publisher;
    dbo::collection< dbo::ptr<class Stock> > stocks;
    
    template<class Action>
    void persist(Action& a) {
        dbo::field(a, title, "title");
        dbo::belongsTo(a, publisher, "publisher");
        dbo::hasMany(a, stocks, dbo::ManyToOne, "book");
    }
};

// Класс магазина
class Shop {
public:
    std::string name;
    dbo::collection< dbo::ptr<class Stock> > stocks;
    
    template<class Action>
    void persist(Action& a) {
        dbo::field(a, name, "name");
        dbo::hasMany(a, stocks, dbo::ManyToOne, "shop");
    }
};

// Класс наличия книг на складе
class Stock {
public:
    dbo::ptr<Book> book;
    dbo::ptr<Shop> shop;
    int count;
    dbo::collection< dbo::ptr<class Sale> > sales;
    
    template<class Action>
    void persist(Action& a) {
        dbo::belongsTo(a, book, "book");
        dbo::belongsTo(a, shop, "shop");
        dbo::field(a, count, "count");
        dbo::hasMany(a, sales, dbo::ManyToOne, "stock");
    }
};

// Класс продаж
class Sale {
public:
    dbo::ptr<Stock> stock;
    double price;
    Wt::WDateTime date_sale;
    int count;
    
    template<class Action>
    void persist(Action& a) {
        dbo::belongsTo(a, stock, "stock");
        dbo::field(a, price, "price");
        dbo::field(a, date_sale, "date_sale");
        dbo::field(a, count, "count");
    }
};

int main() {
    try {
        std::unique_ptr<dbo::backend::Postgres> connection(
            new dbo::backend::Postgres("dbname=bookstore user=postgres password=secret")
        );

        dbo::Session session;
        session.setConnection(std::move(connection));

        session.mapClass<Publisher>("publisher");
        session.mapClass<Book>("book");
        session.mapClass<Shop>("shop");
        session.mapClass<Stock>("stock");
        session.mapClass<Sale>("sale");

        session.createTables();
        
        std::cout << "Database schema created successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
