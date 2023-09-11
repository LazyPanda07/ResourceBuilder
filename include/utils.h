#pragma once

#include <memory>

#include "BaseCompilerParameters.h"

namespace resource_builder
{
    namespace utils
    {
        std::string toHex(uint8_t v);

        std::string getFileName(const std::string& imagePath);

        char getSeparator();

        std::string getCurrentFolder();

        std::unique_ptr<BaseCompilerParameters> createParameters(std::string compilerName);
    }
}
