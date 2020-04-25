//
// Created by red on 4/25/20.
//

#ifndef SQLITEMATE_SQLITEBROKER_H
#define SQLITEMATE_SQLITEBROKER_H

#include <string>
#include <fstream>

namespace sqlite::utilities {

    /** Provides all correspondent requests
     *
     */
    class SQLiteBroker {
    public:
        SQLiteBroker() = delete;
        explicit SQLiteBroker(const std::string& _dbPath);

        static int Callback(void* _data, int _argc, char** _argv, char** _azColName);

        [[nodiscard]] int MakeRequest(const std::string &_requestPath);

    private:
        std::string m_dbPath;
        static inline std::ofstream m_response;

    };
}

#endif //SQLITEMATE_SQLITEBROKER_H
