#pragma once

#include "IOperation.h"


class EchoOperation: public IOperation {
 public:
    explicit EchoOperation(std::string line);
    ~EchoOperation() = default;

    EchoOperation& operator=(const EchoOperation& other) = delete;
    
    void ProcessLine(const std::string& line) override {}
    void HandleEndOfInput() override;
    void SetNextOperation(std::shared_ptr<IOperation> operation) override;

 private:
    std::shared_ptr<IOperation> nextOperation_;
    std::string echoLine_;
};
