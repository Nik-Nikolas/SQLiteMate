//
// Created by red on 4/25/20.
//

#ifndef SQLITEMATE_CONSOLELOGGER_H
#define SQLITEMATE_CONSOLELOGGER_H

#include <string>
#include <iostream>
#include <cassert>

namespace utils {
    class ConsoleLogger {
    public:
        ConsoleLogger() = default;

        static void Log(const std::string& _messageType, const std::string& _message)
        {
            if(_messageType == "message") {
                std::cout << _message << std::endl;
            }
            else if(_messageType == "error") {
                std::cerr << _message << std::endl;
            }
            else if(_messageType == "log") {
                std::clog << _message << std::endl;
            }
            else
            {
                assert(false);
            }
        }
    };
}

#endif //SQLITEMATE_CONSOLELOGGER_H
