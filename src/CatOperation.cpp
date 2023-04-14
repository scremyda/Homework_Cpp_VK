#include "CatOperation.h"
#include "UniqOperation.h"

#include <string>
#include <iostream>
#include <typeinfo>


CatOperation::CatOperation(const std::string& fileName)
    : fileName_(fileName), nextOperation_(nullptr) {
    inputStream_.open(fileName_);
    if (!inputStream_) {
        std::cerr << "Невозможно открыть файл: " << fileName_ << std::endl;
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
