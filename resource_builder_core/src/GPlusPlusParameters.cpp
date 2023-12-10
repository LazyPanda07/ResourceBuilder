#include "GPlusPlusParameters.h"

namespace resource_builder
{
    std::string GPlusPlusParameters::getParameters() const
    {
        return "-shared -fPIC";
    }

    std::string GPlusPlusParameters::getOutputParameter(const std::string& outputPath) const
    {
        return "-o " + outputPath;
    }

    std::string GPlusPlusParameters::getStandard() const
    {
        return "-std=c++11";
    }

    std::string GPlusPlusParameters::getName() const
    {
        return "g++";
    }

    std::string GPlusPlusParameters::getOptimizationLevel() const
    {
        return "-O3";
    }
}
