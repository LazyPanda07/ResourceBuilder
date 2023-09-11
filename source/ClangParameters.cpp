#include "ClangParameters.h"

namespace resource_builder
{
    std::string ClangParameters::getParameters() const
    {
        return "-shared -fPIC";
    }

    std::string ClangParameters::getOutputParameter() const
    {
        return "-o";
    }

    std::string ClangParameters::getStandard() const
    {
        return "-std=c++11";
    }

    std::string ClangParameters::getOptimizationLevel() const
    {
        return "-O3";
    }
}
