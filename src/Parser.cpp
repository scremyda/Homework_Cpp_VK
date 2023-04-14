#include "Parser.hpp"
#include "IOperation.hpp"
#include "CatOperation.hpp"
#include "EchoOperation.hpp"
#include "UniqOperation.hpp"

#include <iostream>


Parser::Parser(char** argv) : streamInput_(argv[1]) {}

Conveyor Parser::Parse() {
    std::vector<std::string> commands;
    std::string command;
    while (std::getline(streamInput_, command, '|')) {
        commands.push_back(command);
    }

    Conveyor conveyor;
    for (const std::string& cmd : commands) {
        std::istringstream iss(cmd);
        std::string function;
        iss >> function;
        std::shared_ptr<IOperation> operation;
        if (function == "cat") {
            std::string filename;
            iss >> filename;
            operation = std::make_shared<CatOperation>(filename);
            if (iss >> filename) {
                throw  std::invalid_argument("Invalid number of arguments for cat <filename>");
            }
        } else if (function == "echo") {
            std::string argument;
            iss >> argument;
            operation = std::make_shared<EchoOperation>(argument);
            if (iss >> argument) {
                throw  std::invalid_argument("Invalid number of arguments for echo <some string>");
            }
        } else if (function == "uniq") {
            operation = std::make_shared<UniqOperation>();
            std::string argument;
            if (iss >> argument) {
                throw  std::invalid_argument("Invalid number of arguments for uniq <zero arguments>");
            }
        } else {
            throw  std::invalid_argument("Invalid command:" + function);
        }
        conveyor.SetOperationBackward(operation);
    }

    return conveyor;
}
