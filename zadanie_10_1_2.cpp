#include <iostream>
#include <string>
#include <unordered_map>

// Имитация тяжелой базы данных
class VeryHeavyDatabase {
private:
    std::unordered_map<std::string, std::string> data;
public:
    VeryHeavyDatabase() {
        data["key"] = "value";
        data["another_key"] = "another_value";
    }

    std::string GetData(const std::string& key) {
        return data.count(key) ? data[key] : "not found";
    }
};

// Класс-заместитель с ограничением числа вызовов
class OneShotDB : public VeryHeavyDatabase {
private:
    VeryHeavyDatabase* real_db;
    size_t remaining_shots;
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1)
        : real_db(real_object), remaining_shots(shots) {}

    std::string GetData(const std::string& key) override {
        if (remaining_shots > 0) {
            --remaining_shots;
            return real_db->GetData(key);
        }
        return "error";
    }
};

// Тестирование
int main() {
    VeryHeavyDatabase real_db;
    OneShotDB limit_db(&real_db, 2);

    std::cout << limit_db.GetData("key") << std::endl;  // value
    std::cout << limit_db.GetData("key") << std::endl;  // value
    std::cout << limit_db.GetData("key") << std::endl;  // error
}
