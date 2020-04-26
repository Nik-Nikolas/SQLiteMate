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

        /** To be called while sqlite3::sqlite3_exec performs the operation(s)
         *
         * @param _data data provided in the 4th argument of sqlite3_exec()
         * @param _argc the number of columns in row
         * @param _argv an array of strings representing fields in the row
         * @param _azColName an array of strings representing column names
         * @return 0 if successful, 1 otherwise
         */
        static int Callback(void* _data, int _argc, char** _argv, char** _azColName);

        /** Makes the SQL request
         *
         * @param _requestPath the text file with the request path
         * @return 0 if successful, 1 otherwise
         */
        [[nodiscard]] int MakeRequest(const std::string &_requestPath);

    private:
        /** Keeps the path to the DB
         *
         */
        std::string m_dbPath;

        /** Ofstream entity
         *
         */
        static inline std::ofstream m_response{};
    };
}

#endif //SQLITEMATE_SQLITEBROKER_H
