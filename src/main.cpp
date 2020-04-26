//
// Created by red on 4/25/20.
//

#include "DefaultNames.h"
#include "SQLiteBroker.h"
#include "utils/ConsoleLogger.h"

#include <string>

int main(int argc, char **argv) {
    std::string dbPath{};
    std::string requestPath{};

    if (argc == 1) {
        auto dbOpt = sqlite::utilities::DefaultNamesConverter::ToString(sqlite::utilities::DefaultNames::dbFile);
        if(dbOpt)
            dbPath = dbOpt.value();

        auto reqOpt = sqlite::utilities::DefaultNamesConverter::ToString(sqlite::utilities::DefaultNames::requestFile);
        if(reqOpt)
            requestPath = reqOpt.value();
    }

    if (argc == 3) {
        dbPath = argv[1];
        requestPath = argv[2];
    }

    if (argc != 1 && argc != 3) {
        utils::ConsoleLogger::Log("error", "Wrong parameters amount!");
        return 1;
    }

    sqlite::utilities::SQLiteBroker broker(dbPath);

    return broker.MakeRequest(requestPath);
}