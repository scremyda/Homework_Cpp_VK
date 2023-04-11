#pragma once

#include <string>
#include <memory>


class IOperation {
 public:
    virtual void ProcessLine(const std::string& str) = 0;

    virtual void HandleEndOfInput() = 0;

    virtual void SetNextOperation(std::shared_ptr<IOperation> operation) = 0;
};
