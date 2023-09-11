#include "ClangPlusPlusParameters.h"

namespace resource_builder
{
    std::string ClangPlusPlusParameters::getParameters() const
    {
        return "-shared -fPIC";
    }

    std::string ClangPlusPlusParameters::getOutputParameter() const
    {
        return "-o";
    }

    std::string ClangPlusPlusParameters::getStandard() const
    {
        return "-std=c++11";
    }

    std::string ClangPlusPlusParameters::getOptimizationLevel() const
    {
        return "-O3";
    }
}
