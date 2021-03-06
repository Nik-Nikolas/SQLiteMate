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

        /** Makes the SQL request
         *
         * @param _requestPath the text file with the request path
         * @return 0 if successful, 1 otherwise
         */
        [[nodiscard]] int MakeRequest(const std::string &_requestPath, const std::string &_request);

    private:
        /** To be called while sqlite3::sqlite3_exec performs the operation(s) while the SELECT query is processing
         *
         * @param _data data provided in the 4th argument of sqlite3_exec()
         * @param _argc the number of columns in row
         * @param _argv an array of strings representing fields in the row
         * @param _colName an array of strings representing column names
         * @return 0 if successful, 1 otherwise
         */
        static int SelectCallback(void *_data, int _argc, char **_argv, char **_colName);

        /** Keeps the path to the DB
         *
         */
        std::string m_dbPath;

        // TODO improve the resource processing: open/close file once for session
        // TODO avoid the static stream resource
        /** Ofstream entity
         *
         */
        static inline std::ofstream m_response{};
    };
}

#endif //SQLITEMATE_SQLITEBROKER_H
