#pragma once

#include <string>
#include <memory>

#include "BaseCompilerParameters.h"

namespace resource_builder
{
    namespace utils
    {
        std::string getResourceBuilderVersion();

        std::string toHex(uint8_t v);

        std::string getFileName(const std::string& imagePath);

        char getSeparator();

        std::string getCurrentFolder();

        std::unique_ptr<resource_builder::BaseCompilerParameters> createParameters(std::string compilerName);

        std::string createResourceCommand(const std::unique_ptr<resource_builder::BaseCompilerParameters>& parameters, const std::string& outputPath);
    }
}
