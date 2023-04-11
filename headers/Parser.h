#pragma once

#include "Conveyer.h"

#include <sstream>


class Parser {
 public:
    explicit Parser(char** argv);
    ~Parser() = default;

    Parser& operator=(const Parser& other) = delete;

    Conveyer Parse();

 private:
    std::string input_;
    std::stringstream streamInput_;
};
