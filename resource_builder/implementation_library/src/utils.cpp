#include "utils.h"

#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>

#ifdef LINUX
#include <unistd.h>
#include <limits.h>
#elif WINDOWS
#include <Windows.h>
#include <minwindef.h>
#endif

namespace resource_builder
{
    namespace utils
    {
        std::string toHex(uint8_t v)
        {
            std::ostringstream ss;

            ss << std::hex << std::setfill('0');

            ss << std::hex << std::setw(2) << static_cast<int>(v);

            return ss.str();
        }

        std::string getFileName(const std::string& imagePath)
        {
            size_t index = imagePath.rfind('/');

            return index == std::string::npos ? imagePath : imagePath.substr(index);
        }

        char getSeparator()
        {
#ifdef LINUX
            return '/';
#elif WINDOWS
            return '\\';
#endif  
        }

        std::string getCurrentFolder()
        {
            std::string result;

#ifdef LINUX
            char path[PATH_MAX]{};

            if (!getcwd(path, sizeof(path)))
            {
                throw std::runtime_error("Can't get current directory path");
            }
#elif WINDOWS
            char path[MAX_PATH]{};

            if (!GetCurrentDirectoryA(sizeof(path), path))
            {
                throw std::runtime_error("Can't get current directory path");
            }
#endif

            result = path;

            result.shrink_to_fit();

            return result;
        }
    }
}
