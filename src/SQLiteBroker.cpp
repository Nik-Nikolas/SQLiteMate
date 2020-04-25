//
// Created by red on 4/25/20.
//

#include "utils/ConsoleLogger.h"
#include "SQLiteBroker.h"
#include "sqlite3/sqlite3.h"

#include <sstream>

sqlite::utilities::SQLiteBroker::SQLiteBroker(const std::string &_dbPath) : m_dbPath(_dbPath) {

}

int sqlite::utilities::SQLiteBroker::Callback(void *_data, int _argc, char **_argv, char **_azColName) {

    utils::ConsoleLogger::Log("message", (const char *) _data);

    // Execute SQL statement
    m_response.open("response.txt", std::ios::app);
    if(!m_response){
        utils::ConsoleLogger::Log("error", "Output file not ready.");
        return 1;
    }

    m_response << "\n-----------------------------------\n";
    utils::ConsoleLogger::Log("message", "\n-----------------------------------\n");
    for (auto i = 0; i < _argc; ++i) {
        const std::string val = _argv[i] ? _argv[i] : "";

        if(!val.empty()) {
            m_response << _azColName[i] << " : " << val << "\n";
            utils::ConsoleLogger::Log("message", std::string(_azColName[i]) + " : " + val);
        }
    }
    m_response << std::endl;

    m_response.close();

    return 0;
}

int sqlite::utilities::SQLiteBroker::MakeRequest(const std::string &_requestPath) {

    sqlite3 *db;
    char *zErrMsg{};
    const char *data = "Callback function called";

    // Open database
    int rc = sqlite3_open(m_dbPath.c_str(), &db);

    if (rc) {
        utils::ConsoleLogger::Log("error", "Can't open database: " + std::string(sqlite3_errmsg(db)));
        return 1;
    } else {
        utils::ConsoleLogger::Log("message", "Opened database successfully.");
    }

    // Read the request from file
    std::stringstream request;
    {
        std::ifstream s(_requestPath);
        if (!s) {
            utils::ConsoleLogger::Log("error", "Request file not available.");
            return 1;
        }
        request << s.rdbuf();
    }

    rc = sqlite3_exec(db, request.str().c_str(), this->Callback, (void *) data, &zErrMsg);

    if (rc != SQLITE_OK) {
        utils::ConsoleLogger::Log("error", "SQL error: " + std::string(zErrMsg));
        sqlite3_free(zErrMsg);
        return 1;
    } else {
        utils::ConsoleLogger::Log("message", "Operation done successfully.");
    }
    sqlite3_close(db);

    return 0;
}
