#include "utils.h"

#include <sstream>
#include <iomanip>
#include <algorithm>

#ifdef LINUX
#include <unistd.h>
#include <limits.h>
#elif WINDOWS
#include <Windows.h>
#endif

#include "GPlusPlusParameters.h"
#include "ClangParameters.h"
#include "CLCompilerParameters.h"

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

            getcwd(path, sizeof(path));

            result = path;
#elif WINDOWS
            char path[MAX_PATH]{};

            GetCurrentDirectory(sizeof(path), path);

            result = path;
#endif

            result.shrink_to_fit();

            return result;
        }

        std::unique_ptr<BaseCompilerParameters> createParameters(std::string compilerName)
        {
            std::for_each(compilerName.begin(), compilerName.end(), [](char& c) { c = tolower(c); });

            if (compilerName == "g++" || compilerName == "gcc")
            {
                return std::unique_ptr<BaseCompilerParameters>(new GPlusPlusParameters());
            }
            else if (compilerName == "clang")
            {
                return std::unique_ptr<BaseCompilerParameters>(new ClangParameters());
            }
            else if (compilerName == "cl" || compilerName == "msvc")
            {
                return std::unique_ptr<BaseCompilerParameters>(new CLCompilerParameters());
            }
            else
            {
                throw std::runtime_error("Wrong compiler name");
            }
        }
    }
}
