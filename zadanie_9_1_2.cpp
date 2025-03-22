#ifndef SQL_QUERY_BUILDER_H
#define SQL_QUERY_BUILDER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>

class SqlSelectQueryBuilder {
private:
    std::vector<std::string> columns;
    std::string table;
    std::unordered_map<std::string, std::string> conditions;

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

    std::string BuildQuery() const {
        std::ostringstream query;
        
        query << "SELECT ";
        if (columns.empty()) {
            query << "*";
        } else {
            for (size_t i = 0; i < columns.size(); ++i) {
                query << columns[i];
                if (i < columns.size() - 1) {
                    query << ", ";
                }
            }
        }
        
        query << " FROM " << table;
        
        if (!conditions.empty()) {
            query << " WHERE ";
            bool first = true;
            for (const auto& [key, value] : conditions) {
                if (!first) {
                    query << " AND ";
                }
                query << key << "=" << value;
                first = false;
            }
        }
        
        query << ";";
        return query.str();
    }
};

#endif // SQL_QUERY_BUILDER_H
