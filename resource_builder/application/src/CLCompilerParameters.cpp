#include "CLCompilerParameters.h"

namespace resource_builder
{
    std::string CLCompilerParameters::getParameters() const
    {
        return "/GL /LD /utf-8 /MT";
    }

    std::string CLCompilerParameters::getOutputParameter() const
    {
        return "/link /IMPLIB:default.lib /OUT:";
    }

    std::string CLCompilerParameters::getStandard() const
    {
        return "/std:c++20";
    }

    std::string CLCompilerParameters::getOptimizationLevel() const
    {
        return "/O2";
    }
}
