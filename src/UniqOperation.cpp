#include "UniqOperation.h"

#include <iostream>
#include <algorithm>

UniqOperation::UniqOperation() : nextOperation_(nullptr) {}

void UniqOperation::ProcessLine(const std::string& line) {
    uniqBuffer_.push_back(line);
}

void UniqOperation::HandleEndOfInput() {
    uniqBuffer_.erase(std::unique(uniqBuffer_.begin(), uniqBuffer_.end()),
    uniqBuffer_.end());

    for (const auto& line : uniqBuffer_) {
        if (nextOperation_) {
            nextOperation_->ProcessLine(line);
        } else {
            std::cout << line << std::endl;
        }
    }

    if (nextOperation_) {
        nextOperation_->HandleEndOfInput();
    }
}

void UniqOperation::SetNextOperation(std::shared_ptr<IOperation> operation) {
    nextOperation_ = operation;
}
