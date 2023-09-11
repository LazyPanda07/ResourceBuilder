#include "GPlusPlusParameters.h"

namespace resource_builder
{
    std::string GPlusPlusParameters::getParameters() const
    {
        return "-shared -fPIC";
    }

    std::string GPlusPlusParameters::getOutputParameter() const
    {
        return "-o";
    }

    std::string GPlusPlusParameters::getStandard() const
    {
        return "-std=c++11";
    }

    std::string GPlusPlusParameters::getOptimizationLevel() const
    {
        return "-O3";
    }
}
