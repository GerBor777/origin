#ifndef SQL_QUERY_BUILDER_H
#define SQL_QUERY_BUILDER_H

#include <string>
#include <vector>
#include <map>
#include <sstream>

class SqlSelectQueryBuilder {
private:
    std::vector<std::string> columns;
    std::string table;
    std::map<std::string, std::string> conditions;

public:
    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& cols) noexcept {
        columns.insert(columns.end(), cols.begin(), cols.end());
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table_name) {
        table = table_name;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        conditions[column] = value;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        conditions.insert(kv.begin(), kv.end());
        return *this;
    }

    SqlSelectQueryBuilder& Clear() noexcept {
        columns.clear();
        table.clear();
        conditions.clear();
        return *this;
    }

    std::string BuildQuery() const {
        if (table.empty()) {
            return "";
        }

        std::ostringstream query;
        query << "SELECT ";

        if (columns.empty()) {
            query << "*";
        } else {
            for (size_t i = 0; i < columns.size(); ++i) {
                if (i > 0) query << ", ";
                query << columns[i];
            }
        }

        query << " FROM " << table;

        if (!conditions.empty()) {
            query << " WHERE ";
            bool first = true;
            for (const auto& [key, value] : conditions) {
                if (!first) query << " AND ";
                query << key << "=" << value;
                first = false;
            }
        }

        query << ";";
        return query.str();
    }
};

#endif // SQL_QUERY_BUILDER_H
