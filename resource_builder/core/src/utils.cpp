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

#include "GPlusPlusParameters.h"
#include "ClangPlusPlusParameters.h"
#include "CLCompilerParameters.h"
#include "ResourceFileGenerator.h"

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

        std::unique_ptr<resource_builder::BaseCompilerParameters> createParameters(std::string compilerName)
        {
            auto contains = [](const std::string& source, const std::string& substring)
                {
                    return source.find(substring) != std::string::npos;
                };

            std::for_each(compilerName.begin(), compilerName.end(), [](char& c) { c = tolower(c); });

            if (contains(compilerName, "clang") || contains(compilerName, "clang++"))
            {
                return std::unique_ptr<resource_builder::BaseCompilerParameters>(new resource_builder::ClangPlusPlusParameters());
            }

            if (contains(compilerName, "gcc") || contains(compilerName, "g++"))
            {
                return std::unique_ptr<resource_builder::BaseCompilerParameters>(new resource_builder::GPlusPlusParameters());
            }

            if (contains(compilerName, "cl") || contains(compilerName, "msvc"))
            {
                return std::unique_ptr<resource_builder::BaseCompilerParameters>(new resource_builder::CLCompilerParameters());
            }

            throw std::runtime_error("Wrong compiler name");
        }

        std::string createResourceCommand(const std::unique_ptr<resource_builder::BaseCompilerParameters>& parameters, const std::string& outputPath)
        {
            return '\"' + parameters->getName() + '\"' + ' ' +
                parameters->getStandard() + ' ' +
                parameters->getParameters() + ' ' +
                parameters->getOptimizationLevel() + ' ' +
                resource_builder::ResourceFileGenerator::resourceFileName + ' ' +
                parameters->getOutputParameter(outputPath);
        }
    }
}
