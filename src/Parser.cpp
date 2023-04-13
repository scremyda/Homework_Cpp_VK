#include "Parser.h"
#include "IOperation.h"
#include "CatOperation.h"
#include "EchoOperation.h"
#include "UniqOperation.h"

#include <iostream>


Parser::Parser(char** argv) : input_(argv[1]), streamInput_(input_) {}

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
                std::cerr <<
                "Было задано неверное кол-во аргументов для cat <filename>"
                << std::endl;
                conveyor.SetError();
            }
        } else if (function == "echo") {
            std::string argument;
            iss >> argument;
            operation = std::make_shared<EchoOperation>(argument);
            if (iss >> argument) {
                std::cerr <<
                "Было задано неверное кол-во аргументов для echo <some string>"
                << std::endl;
                conveyor.SetError();
            }
        } else if (function == "uniq") {
            operation = std::make_shared<UniqOperation>();
            std::string argument;
            if (iss >> argument) {
                std::cerr <<
                "Было задано неверное кол-во аргументов для uniq <zero arguments>"
                << std::endl;
                conveyor.SetError();
            }
        } else {
            std::cerr <<
            "Введенной команды " << function << " нет в списке команд."
            << std::endl;
            std::cerr <<
            "Список команд: echo <some string>, cat <filename>, uniq <zero arguments>"
            << std::endl;
            conveyor.SetError();
        }
        if (operation) {
            conveyor.SetOperation(operation);
        }
    }

    return conveyor;
}
