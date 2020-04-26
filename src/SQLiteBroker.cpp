//
// Created by red on 4/25/20.
//

#include "utils/DefaultNames.h"

#include "utils/ConsoleLogger.h"
#include "SQLiteBroker.h"
#include "sqlite3/sqlite3.h"

#include <sstream>
#include <filesystem>

sqlite::utilities::SQLiteBroker::SQLiteBroker(const std::string &_dbPath) : m_dbPath(_dbPath) {

    // Remove the old output file to avoid appending data to the existent one
    {
        std::string responseFile{};
        auto resOpt = sqlite::utilities::DefaultNamesConverter::ToString(sqlite::utilities::DefaultNames::responseFile);
        if(resOpt)
            responseFile = resOpt.value();

        std::error_code ec{};
        auto res = std::filesystem::remove(responseFile, ec);

        if(!res)
            utils::ConsoleLogger::Log("error", "Output file was not clear.");
    }
}

int sqlite::utilities::SQLiteBroker::Callback(void *_data, int _argc, char **_argv, char **_azColName) {

    // Default response file opening
    {
        utils::ConsoleLogger::Log("message", (const char *) _data);

        std::string responseFile{};
        auto resOpt = sqlite::utilities::DefaultNamesConverter::ToString(sqlite::utilities::DefaultNames::responseFile);
        if(resOpt)
            responseFile = resOpt.value();

        m_response.open(responseFile, std::ios::app);
        if(!m_response){
            utils::ConsoleLogger::Log("error", "Output file not ready.");
            return 1;
        }
    }

    // Output the data to the file
    {
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
    }

    return 0;
}

int sqlite::utilities::SQLiteBroker::MakeRequest(const std::string &_requestPath) {

    // Open database
    sqlite3 *db;
    {
        auto res = sqlite3_open(m_dbPath.c_str(), &db);
        if (res) {
            utils::ConsoleLogger::Log("error", "Can't open the database: " + std::string(sqlite3_errmsg(db)));
            return 1;
        } else {
            utils::ConsoleLogger::Log("message", "Opened database successfully.");
        }
    }

    // Read the request from file
    std::stringstream request;
    {
        std::ifstream stream(_requestPath);
        if (!stream) {
            utils::ConsoleLogger::Log("error", "Request file not available.");
            return 1;
        }
        request << stream.rdbuf();
    }

    // Execute SQL statement
    {
        const auto tmp = request.str();
        char *errMsg{};
        const auto data = "Callback function called";
        auto res = sqlite3_exec(db, tmp.c_str(), this->Callback, (void *)data, &errMsg);

        // Analyze the results and output the conclusion
        if (res != SQLITE_OK) {
            utils::ConsoleLogger::Log("error", "SQL error: " + std::string(errMsg));
            sqlite3_free(errMsg);
            return 1;
        } else {
            utils::ConsoleLogger::Log("message", "Operation done successfully.");
        }
        sqlite3_close(db);
    }

    return 0;
}
