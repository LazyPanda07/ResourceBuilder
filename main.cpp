#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

#include "utils.h"

/**
 * @param argv Compiler<cl, g++, clang>, output path, <--keep, --ignore_resource_error> || resource paths
 */
int main(int argc, char** argv)
{
    try
    {
        std::cout << "Usage: compiler<cl, g++, clang>, output path, <--keep, --ignore_resource_error> || resource paths" << std::endl <<
            "keep - keep generated tem.cpp file" << std::endl <<
            "ignore_resource_error - ignore wrong resource path" << std::endl;

        if (argc < 4)
        {
            std::cout << "Compiler, output path and resource path must be specified" << std::endl;

            return -1;
        }

        std::string compilerName = argv[1];
        std::string outputPath = argv[2];
        std::ostringstream resultFile;
        bool keep = false;
        bool ignore_resource_error = false;
        std::unique_ptr<resource_builder::BaseCompilerParameters> parameters = resource_builder::utils::createParameters(compilerName);
        std::string getterSignature = "extern \"C\" ";

        if (outputPath.find(resource_builder::utils::getSeparator()) == std::string::npos)
        {
            outputPath = resource_builder::utils::getCurrentFolder() + resource_builder::utils::getSeparator() + outputPath;
        }

        resultFile << "#include <string>" << std::endl;
        resultFile << "#include <stdexcept>" << std::endl;
        resultFile << "#include <unordered_map>" << std::endl;
        resultFile << "#include <vector>" << std::endl << std::endl;
        resultFile << "static const std::unordered_map<std::string, std::vector<uint8_t>> data = " << std::endl << '{' << std::endl;

        for (size_t i = 3; i < argc; i++)
        {
            std::string resourcePath = argv[i];

            if (resourcePath == "--keep")
            {
                keep = true;

                continue;
            }
            else if (resourcePath == "--ignore_resource_error")
            {
                ignore_resource_error = true;

                continue;
            }

            std::ifstream resource(resourcePath, std::ios::binary);
            std::ostringstream data;
            std::string fileData;

            if (!resource.is_open())
            {
                std::cout << "Can't open file: " << resourcePath << std::endl;

                if (ignore_resource_error)
                {
                    continue;
                }

                return -2;
            }

            data << resource.rdbuf();

            fileData = data.str();

            resultFile << "\t{" << std::endl << "\t\t\"" << resource_builder::utils::getFileName(resourcePath) << "\"," << std::endl << "\t\t" << '{' << std::endl << "\t\t\t";

            for (size_t j = 0; j < fileData.size(); j++)
            {
                resultFile << "0x" << resource_builder::utils::toHex(fileData[j]);

                if (j + 1 != fileData.size())
                {
                    resultFile << ", ";
                }

                if (j && !((j + 1) % 16))
                {
                    resultFile << std::endl << "\t\t\t";
                }
            }

            resultFile << std::endl << "\t\t}" << std::endl;
            resultFile << "\t}";

            if (i + 1 != argc)
            {
                resultFile << ',' << std::endl;
            }
        }

        resultFile << std::endl << "};" << std::endl << std::endl;

#ifdef LINUX
        getterSignature += "__attribute__ ((visibility (\"default\")))";
#elif WINDOWS   
        getterSignature += "__declspec(dllexport)";
#endif

        resultFile << getterSignature << R"( const std::vector<uint8_t>& getResource(const std::string& resourceName)
{
	auto it = data.find(resourceName);

	if (it == data.end())
	{
		throw std::runtime_error("Can't find resource with name: " + resourceName);
	}

	return it->second;
})" << std::endl;

        std::ofstream("tem.cpp") << resultFile.str();

        std::string extension;
        std::string command = '\"' + compilerName + "\" " +
            parameters->getStandard() + ' ' +
            parameters->getParameters() + ' ' +
            parameters->getOptimizationLevel() + ' ' +
            "tem.cpp" + ' ' +
            parameters->getOutputParameter() +
#ifdef LINUX 
            ' '
#elif WINDOWS
            '\"'
#endif
            ;

        command.append(outputPath);

#ifdef LINUX
        extension = ".so";
#elif WINDOWS
        extension = ".dll";

        command.insert(0, "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Enterprise\\VC\\Auxiliary\\Build\\vcvars64.bat\" && ");
#endif

        if (outputPath.find(extension) == std::string::npos)
        {
            command.append(extension);
        }

#ifdef WINDOWS
        command += '\"';
#endif

        if (system(command.data()))
        {
            throw std::runtime_error("Can't execute command: " + command);
        }

        if (!keep)
        {
            if (system("rm tem.cpp"))
            {
                throw std::runtime_error("Can't remove tem.cpp");
            }
        }

        std::cout << "Output resources path: " << outputPath << std::endl;

    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
