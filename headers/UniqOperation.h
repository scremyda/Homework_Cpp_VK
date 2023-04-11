#pragma once

#include "IOperation.h"

#include <vector>


class UniqOperation: public IOperation {
 public:
    UniqOperation();
    ~UniqOperation() = default;

    UniqOperation& operator=(const UniqOperation& other) = delete;;

    void ProcessLine(const std::string& line) override;
    void HandleEndOfInput() override;
    void SetNextOperation(std::shared_ptr<IOperation> operation) override;

 private:
    std::shared_ptr<IOperation> nextOperation_;
    std::vector<std::string> uniqBuffer_;
};
