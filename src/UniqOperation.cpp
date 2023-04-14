#include "CatOperation.h"
#include "UniqOperation.h"

#include <iostream>
#include <algorithm>


UniqOperation::UniqOperation() : nextOperation_(nullptr) {}

void UniqOperation::ProcessLine(const std::string& line) {
    if (nextOperation_ && line != previousLine_) {
        nextOperation_->ProcessLine(line);
    } else if (!nextOperation_ && line != previousLine_) {
        std::cout << line << std::endl;
    }
    previousLine_ = line;
}

void UniqOperation::HandleEndOfInput() {
    if (nextOperation_) {
        nextOperation_->HandleEndOfInput();
    }
}

void UniqOperation::SetNextOperation(std::shared_ptr<IOperation> operation) {
    nextOperation_ = operation;
}
