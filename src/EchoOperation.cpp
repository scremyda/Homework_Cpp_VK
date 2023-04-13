#include "EchoOperation.h"

#include <iostream>


EchoOperation::EchoOperation(const std::string& line) :
echoLine_(line), nextOperation_(nullptr) {}

void EchoOperation::HandleEndOfInput() {
    if (nextOperation_) {
        nextOperation_->ProcessLine(echoLine_);
        nextOperation_->HandleEndOfInput();
    } else {
        std::cout << echoLine_ << std::endl;
    }
}

void EchoOperation::SetNextOperation(std::shared_ptr<IOperation> operation) {
    nextOperation_ = operation;
}
