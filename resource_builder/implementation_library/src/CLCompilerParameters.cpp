#include "CLCompilerParameters.h"

namespace resource_builder
{
    std::string CLCompilerParameters::getParameters() const
    {
        return "/LD /utf-8 /MT";
    }

    std::string CLCompilerParameters::getOutputParameter(const std::string& outputPath) const
    {
        return "/link /IMPLIB:default.lib /OUT:" + outputPath;
    }

    std::string CLCompilerParameters::getStandard() const
    {
        return "/std:c++20";
    }

    std::string CLCompilerParameters::getName() const
    {
        return "cl";
    }

    std::string CLCompilerParameters::getOptimizationLevel() const
    {
        return "/O2";
    }
}
