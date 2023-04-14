#include "Conveyor.hpp"


void Conveyor::SetOperation(const std::shared_ptr<IOperation>& operation) {
    operations_.push_back(operation);
}

void Conveyor::MakeConveyer() {
    for (size_t i = 0; i < operations_.size() - 1; ++i) {
        operations_[i]->SetNextOperation(operations_[i + 1]);
    }
}

void Conveyor::RunConveyer() {
    operations_[0]->HandleEndOfInput();
}
