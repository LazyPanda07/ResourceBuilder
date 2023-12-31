#pragma once

#include "BaseCompilerParameters.h"

namespace resource_builder
{
    class ClangPlusPlusParameters : public BaseCompilerParameters
    {
    public:
        ClangPlusPlusParameters() = default;

        std::string getParameters() const override;

        std::string getOptimizationLevel() const override;

        std::string getStandard() const override;

        std::string getName() const override;

        std::string getOutputParameter(const std::string& outputPath) const override;

        ~ClangPlusPlusParameters() = default;
    };
}
