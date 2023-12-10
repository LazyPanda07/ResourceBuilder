#include "BaseCompilerParameters.h"

namespace resource_builder
{
    std::string BaseCompilerParameters::getOptimizationLevel() const
    {
        return "-O2";
    }
}
