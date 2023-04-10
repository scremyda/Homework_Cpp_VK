#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "headers/IOperation.h"

class IOperation {
public:
    virtual void ProcessLine(const std::string& str) = 0;
    virtual void HandleEndOfInput() = 0;
    virtual void SetNextOperation(std::shared_ptr<IOperation> operation) = 0;
};

class CatOperation: public IOperation {
public:
    explicit CatOperation(std::string fileName) : fileName_(std::move(fileName)), nextOperation_(nullptr) {
        inputStream_.open(fileName_);
        if (!inputStream_) {
            std::cerr << "Cannot open file: " << fileName_ << std::endl;
        }
    }
    ~CatOperation() {
        if (inputStream_.is_open()) {
            inputStream_.close();
        }
    }

    CatOperation& operator=(const CatOperation& other) = delete;

    void ProcessLine(const std::string& line) override {
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



int main(int argc, char* argv[]) {

    std::vector<std::shared_ptr<IOperation>> operations;
    std::string input(argv[1]);
    std::getline(std::cin, input);
    input.erase(input.begin());
    input.pop_back();
    std::stringstream ss(input);
    std::vector<std::string> commands; 
    std::string command;
    while (std::getline(ss, command, '|')) {
        commands.push_back(command); 
    }


    for (const std::string& cmd : commands) {
        std::shared_ptr<IOperation> operation;

        std::istringstream iss(cmd);
        std::string function;
        iss >> function; 
        if (function == "cat") {
            std::string filename;
            iss >> filename; 
            operation = std::make_shared<CatOperation>(filename);
        }
        else if (function == "echo") {
            std::string text;
            iss >> text; 
            operation = std::make_shared<EchoOperation>(text);
        }
        else if (function == "uniq") {
            operation = std::make_shared<UniqOperation>();
        }
        if (operation) {
            operations.push_back(std::move(operation));
        }
    }
    for (size_t i = 0; i < operations.size() - 1; ++i) {
        operations[i]->SetNextOperation(operations[i+1]);
    }
    operations[0]->HandleEndOfInput();


    return 0;
}
