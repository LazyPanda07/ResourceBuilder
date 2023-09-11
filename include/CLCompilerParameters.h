#pragma once

#include "BaseCompilerParameters.h"

namespace resource_builder
{
    class CLCompilerParameters : public BaseCompilerParameters
    {
    public:
        virtual std::string getParameters() const override;

        virtual std::string getOutputParameter() const override;

        virtual std::string getStandard() const override;

        virtual std::string getOptimizationLevel() const override;
    };
}
