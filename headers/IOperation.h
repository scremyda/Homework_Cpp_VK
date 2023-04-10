#pragma once

#include <string>
#include <memory>


class IOperation {
 public:
    virtual void IOperation::ProcessLine(const std::string& str) = 0;
    virtual void IOperation::HandleEndOfInput() = 0;
    virtual void IOperation::SetNextOperation(std::shared_ptr<IOperation> operation) = 0;
};

class CatOperation: public IOperation {
 public:
    explicit CatOperation(std::string fileName);
    
    ~CatOperation();

    CatOperation& CatOperation::operator=(const CatOperation& other) = delete;

    void ProcessLine(const std::string& line) override;
    
    void HandleEndOfInput() override;

    void SetNextOperation(std::shared_ptr<IOperation> operation) override;

 private:
    std::string fileName_;
    std::shared_ptr<IOperation> nextOperation_;
    std::ifstream inputStream_;
    std::vector<std::string> catBuffer_;
};


class EchoOperation: public IOperation {
 public:
    explicit EchoOperation(std::string line);

    EchoOperation& operator=(const EchoOperation& other);
    
    ~EchoOperation();

    void ProcessLine(const std::string& line) override;

    void HandleEndOfInput() override;

    void SetNextOperation(std::shared_ptr<IOperation> operation) override;

 private:
    std::shared_ptr<IOperation> nextOperation_;
    std::string echoLine_;
};


class UniqOperation: public IOperation {
 public:
    UniqOperation();

    UniqOperation& operator=(const UniqOperation& other);
    
    ~UniqOperation();

    void ProcessLine(const std::string& line) override;

    void HandleEndOfInput() override;

    void SetNextOperation(std::shared_ptr<IOperation> operation) override;

 private:
    std::shared_ptr<IOperation> nextOperation_;
    std::vector<std::string> uniqBuffer_;
};
