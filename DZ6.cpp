#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class ClientDB {
private:
    connection C;

public:
    ClientDB(const string &conn_str) : C(conn_str) {}

    void createTables() {
        work W(C);
        W.exec("""
            CREATE TABLE IF NOT EXISTS clients (
                id SERIAL PRIMARY KEY,
                first_name VARCHAR(50),
                last_name VARCHAR(50),
                email VARCHAR(100) UNIQUE
            );
            CREATE TABLE IF NOT EXISTS phones (
                id SERIAL PRIMARY KEY,
                client_id INT REFERENCES clients(id) ON DELETE CASCADE,
                phone VARCHAR(20) UNIQUE
            );
        """);
        W.commit();
        cout << "Tables created successfully." << endl;
    }

    void addClient(const string &first_name, const string &last_name, const string &email) {
        work W(C);
        W.exec_params("INSERT INTO clients (first_name, last_name, email) VALUES ($1, $2, $3)", first_name, last_name, email);
        W.commit();
        cout << "Client added." << endl;
    }

    void addPhone(int client_id, const string &phone) {
        work W(C);
        W.exec_params("INSERT INTO phones (client_id, phone) VALUES ($1, $2)", client_id, phone);
        W.commit();
        cout << "Phone added." << endl;
    }

    void updateClient(int id, const string &first_name, const string &last_name, const string &email) {
        work W(C);
        W.exec_params("UPDATE clients SET first_name = $1, last_name = $2, email = $3 WHERE id = $4", first_name, last_name, email, id);
        W.commit();
        cout << "Client updated." << endl;
    }

    void deletePhone(const string &phone) {
        work W(C);
        W.exec_params("DELETE FROM phones WHERE phone = $1", phone);
        W.commit();
        cout << "Phone deleted." << endl;
    }

    void deleteClient(int id) {
        work W(C);
        W.exec_params("DELETE FROM clients WHERE id = $1", id);
        W.commit();
        cout << "Client deleted." << endl;
    }

    void findClient(const string &query) {
        nontransaction N(C);
        result R = N.exec("""
            SELECT c.id, c.first_name, c.last_name, c.email, p.phone
            FROM clients c
            LEFT JOIN phones p ON c.id = p.client_id
            WHERE c.first_name = $1 OR c.last_name = $1 OR c.email = $1 OR p.phone = $1;
        """, query);

        for (const auto &row : R) {
            cout << "ID: " << row["id"].as<int>() << ", Name: " << row["first_name"].c_str()
                 << " " << row["last_name"].c_str() << ", Email: " << row["email"].c_str()
                 << ", Phone: " << (row["phone"].is_null() ? "None" : row["phone"].c_str()) << endl;
        }
    }
};

int main() {
    string conn_str = "dbname=test user=postgres password=yourpassword host=localhost";
    ClientDB db(conn_str);

    db.createTables();
    db.addClient("John", "Doe", "john@example.com");
    db.addPhone(1, "123456789");
    db.updateClient(1, "John", "Doe", "john.doe@example.com");
    db.findClient("John");
    db.deletePhone("123456789");
    db.deleteClient(1);

    return 0;
}
