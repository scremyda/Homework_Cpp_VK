#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>

#include "IOperation.h"




CatOperation::CatOperation(std::string fileName) : fileName_(std::move(fileName)), nextOperation_(nullptr) {
    inputStream_.open(fileName_);
    if (!inputStream_) {
        std::cerr << "Cannot open file: " << fileName_ << std::endl;
    }
}

CatOperation::~CatOperation() {
    if (inputStream_.is_open()) {
        inputStream_.close();
    }
}


void CatOperation::ProcessLine(const std::string& line) override {
    catBuffer_.push_back(line);
}

    void HandleEndOfInput() override {
        std::string fileLine;

        while (std::getline(inputStream_, fileLine)) {
            ProcessLine(fileLine);
        }

        for (const auto& line : catBuffer_) {
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

    void SetNextOperation(std::shared_ptr<IOperation> operation) override {
        nextOperation_ = operation;
    }

 private:
    std::string fileName_;
    std::shared_ptr<IOperation> nextOperation_;
    std::ifstream inputStream_;
    std::vector<std::string> catBuffer_;
};


class EchoOperation: public IOperation {
 public:
    explicit EchoOperation(std::string line) : echoLine_(std::move(line)), nextOperation_(nullptr) {}

    EchoOperation& operator=(const EchoOperation& other) = delete;
    
    ~EchoOperation() = default;

    void ProcessLine(const std::string& line) override {
        echoLine_ = line;
    }

    void HandleEndOfInput() override {
        ProcessLine(echoLine_);
        if (nextOperation_) {
            nextOperation_->ProcessLine(echoLine_);
            nextOperation_->HandleEndOfInput();
        } else {
            std::cout << echoLine_ << std::endl;
        }
    }

    void SetNextOperation(std::shared_ptr<IOperation> operation) override {
        nextOperation_ = operation;
    }

 private:
    std::shared_ptr<IOperation> nextOperation_;
    std::string echoLine_;
};


class UniqOperation: public IOperation {
 public:
    UniqOperation() = default;

    UniqOperation& operator=(const UniqOperation& other) = delete;
    
    ~UniqOperation() = default;

    void ProcessLine(const std::string& line) override {
        uniqBuffer_.push_back(line);
    }

    void HandleEndOfInput() override {

        uniqBuffer_.erase(std::unique(uniqBuffer_.begin(), uniqBuffer_.end()), uniqBuffer_.end());

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
    void SetNextOperation(std::shared_ptr<IOperation> operation) override {
        nextOperation_ = operation;
    }

 private:
    std::shared_ptr<IOperation> nextOperation_;
    std::vector<std::string> uniqBuffer_;
};
