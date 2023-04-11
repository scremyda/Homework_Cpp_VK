#include "Conveyer.h"


void Conveyer::SetError() {
    errors_ = true;
}

bool Conveyer::GetError() {
    return errors_;
}

void Conveyer::SetOperation(const std::shared_ptr<IOperation>& operation) {
    operations_.push_back(operation);
}

void Conveyer::MakeConveyer() {
    for (size_t i = 0; i < operations_.size() - 1; ++i) {
        operations_[i]->SetNextOperation(operations_[i + 1]);
    }
}

void Conveyer::RunConveyer() {
    operations_[0]->HandleEndOfInput();
}
