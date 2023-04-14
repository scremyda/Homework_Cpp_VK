#pragma once

#include "IOperation.h"

#include <vector>


class Conveyor {
 public:
    void SetOperation(const std::shared_ptr<IOperation>& operation);

    void MakeConveyer();

    void RunConveyer();
 private:
    std::vector<std::shared_ptr<IOperation>> operations_;
};
