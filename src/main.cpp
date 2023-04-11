#include "IOperation.h"
#include "EchoOperation.h"
#include "CatOperation.h"
#include "UniqOperation.h"
#include "Parser.h"
#include "Conveyer.h"

#include <iostream>


int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "Неверное кол-во аргументов программы." << std::endl;
        return 1;
    }

    Parser parser(argv);
    Conveyer conveyor = parser.Parse();

    if (conveyor.GetError()) {
        return 1;
    }

    conveyor.MakeConveyer();

    conveyor.RunConveyer();

    return 0;
}