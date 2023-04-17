#include "Parser.hpp"
#include "Conveyor.hpp"

#include <iostream>


int main(int argc, char** argv) {
    try {
        if (argc != 2) {
            throw std::invalid_argument("Invalid number of arguments for program");
        }

        Parser parser(argv);

        Conveyor conveyor = parser.Parse();
        
        conveyor.MakeConveyer();
        conveyor.RunConveyer();
    } catch (const std::exception& exception) {
        std::cerr << "Exception occurred: " << exception.what() << std::endl;
        return 1;
    }
    
    return 0;
}
