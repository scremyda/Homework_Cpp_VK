#pragma once

#include "IOperation.h"

#include <vector>


class Conveyer {
 public:
    void SetOperation(const std::shared_ptr<IOperation>& operation);

    void SetError();

    bool GetError();

    void MakeConveyer();

    void RunConveyer();

 private:
    std::vector<std::shared_ptr<IOperation>> operations_;
    bool errors_ = false;
};
