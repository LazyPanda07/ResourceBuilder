#pragma once

#include <string>

namespace resource_builder
{
    class BaseCompilerParameters
    {
    public:
        BaseCompilerParameters() = default;

        virtual std::string getParameters() const = 0;

        virtual std::string getOutputParameter() const = 0;

        virtual std::string getStandard() const = 0;

        virtual std::string getOptimizationLevel() const;

        virtual ~BaseCompilerParameters() = default;
    };
}
