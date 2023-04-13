#pragma once

#include "Conveyor.h"

#include <sstream>


class Parser {
 public:
    explicit Parser(char** argv);
    ~Parser() = default;

    Parser& operator=(const Parser& other) = delete;

    Conveyor Parse();

 private:
    std::string input_;
    std::stringstream streamInput_;
};
