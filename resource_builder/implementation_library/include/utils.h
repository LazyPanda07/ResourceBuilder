#pragma once

#include <string>

namespace resource_builder
{
    namespace utils
    {
        std::string toHex(uint8_t v);

        std::string getFileName(const std::string& imagePath);

        char getSeparator();

        std::string getCurrentFolder();
    }
}
