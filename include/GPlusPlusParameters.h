#pragma once

#include "BaseCompilerParameters.h"

namespace resource_builder
{
    class GPlusPlusParameters : public BaseCompilerParameters
    {
    public:
        GPlusPlusParameters() = default;

        std::string getParameters() const override;

        std::string getOptimizationLevel() const override;

        std::string getStandard() const override;

        std::string getOutputParameter() const override;

        ~GPlusPlusParameters() = default;
    };
}
