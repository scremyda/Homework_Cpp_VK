#pragma once

#include "IOperation.hpp"

#include <vector>


class Conveyor {
 public:
    void SetOperationBackward(const std::shared_ptr<IOperation>& operation);

    void MakeConveyer();

    void RunConveyer();
 private:
    std::vector<std::shared_ptr<IOperation>> operations_;
};
