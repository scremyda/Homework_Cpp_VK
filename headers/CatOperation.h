#pragma once

#include "IOperation.h"

#include <fstream>
#include <vector>



class CatOperation : public IOperation {
public:
    explicit CatOperation(std::string fileName);
    ~CatOperation();

    CatOperation& operator=(const CatOperation& other) = delete;

    void ProcessLine(const std::string& line) override;
    void HandleEndOfInput() override;
    void SetNextOperation(std::shared_ptr<IOperation> operation) override;

private:
    std::string fileName_;
    std::shared_ptr<IOperation> nextOperation_;
    std::ifstream inputStream_;
    std::vector<std::string> catBuffer_;
};
