#include "CatOperation.hpp"

#include <iostream>


CatOperation::CatOperation(const std::string& fileName)
    : fileName_(fileName), nextOperation_(nullptr) {
    inputStream_.open(fileName_);
    if (!inputStream_) {
        throw std::runtime_error("Unable to open the file: " + fileName_);
    }
}

CatOperation::~CatOperation() {
    if (inputStream_.is_open()) {
        inputStream_.close();
    }
}

void CatOperation::ProcessLine(const std::string& line) {
    if (nextOperation_) {
        nextOperation_->ProcessLine(line);
    } else {
        std::cout << line << std::endl;
    }
}

void CatOperation::HandleEndOfInput() {
    std::string fileLine;

    while (std::getline(inputStream_, fileLine)) {
        if (nextOperation_) {
            nextOperation_->ProcessLine(fileLine);
        } else {
            std::cout << fileLine << std::endl;
        }
    }
    if (nextOperation_) {
        nextOperation_->HandleEndOfInput();
    }
}

void CatOperation::SetNextOperation(std::shared_ptr<IOperation> operation) {
    nextOperation_ = operation;
}
