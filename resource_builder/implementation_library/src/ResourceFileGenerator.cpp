#include "ResourceFileGenerator.h"

#include <fstream>
#include <sstream>

#include "utils.h"

namespace resource_builder
{
	const std::string ResourceFileGenerator::resourceFileName = "resource_temp.cpp";

	void ResourceFileGenerator::generateHeaders(std::ofstream& resourceFile)
	{
		resourceFile << "#include <string>" << std::endl;
		resourceFile << "#include <stdexcept>" << std::endl;
		resourceFile << "#include <unordered_map>" << std::endl;
		resourceFile << "#include <vector>" << std::endl;
		resourceFile << "#include <cstdint>" << std::endl << std::endl;
	}

	ResourceFileGenerator::ResourceFileGenerator(int argc, char** argv) :
		argc(argc),
		argv(argv)
	{

	}

	void ResourceFileGenerator::createResourceFile(bool& keep) const
	{
		std::string exportSpecifier = R"(extern "C" )";
		bool ignoreResourceError = false;
		std::ofstream result(ResourceFileGenerator::resourceFileName);

		if (!result.is_open())
		{
			throw std::runtime_error("Can't create resource file");
		}

		ResourceFileGenerator::generateHeaders(result);

		result << "static const std::unordered_map<std::string, std::vector<uint8_t>> data = " << std::endl << '{' << std::endl;

		for (size_t i = 0; i < argc; i++)
		{
			std::string resourcePath = argv[i];

			if (resourcePath == "--keep")
			{
				keep = true;

				continue;
			}
			else if (resourcePath == "--ignore_resource_error")
			{
				ignoreResourceError = true;

				continue;
			}

			std::ifstream resource(resourcePath, std::ios::binary);
			std::ostringstream data;
			std::string fileData;

			if (!resource.is_open())
			{
				if (ignoreResourceError)
				{
					continue;
				}

				throw std::runtime_error("Can't open file: " + resourcePath);
			}

			data << resource.rdbuf();

			fileData = data.str();

			result << "\t{" << std::endl << "\t\t\"" << resource_builder::utils::getFileName(resourcePath) << "\"," << std::endl << "\t\t" << '{' << std::endl << "\t\t\t";

			for (size_t j = 0; j < fileData.size(); j++)
			{
				result << "0x" << resource_builder::utils::toHex(fileData[j]);

				if (j + 1 != fileData.size())
				{
					result << ", ";
				}

				if (j && !((j + 1) % 16))
				{
					result << std::endl << "\t\t\t";
				}
			}

			result << std::endl << "\t\t}" << std::endl;
			result << "\t}";

			if (i + 1 != argc)
			{
				result << ',' << std::endl;
			}
		}

		result << std::endl << "};" << std::endl << std::endl;

#ifdef LINUX
		exportSpecifier += R"(__attribute__ ((visibility ("default"))))";
#elif WINDOWS   
		exportSpecifier += "__declspec(dllexport)";
#endif

		result << exportSpecifier << R"( const std::vector<uint8_t>& getResource(const std::string& resourceName)
{
	auto it = data.find(resourceName);

	if (it == data.end())
	{
		throw std::runtime_error("Can't find resource with name: " + resourceName);
	}

	return it->second;
})" << std::endl << std::endl;

		result << exportSpecifier << R"( const uint8_t* c_getResource(const char* resourceName, size_t* size)
{
	auto it = data.find(resourceName);

	if (it == data.end())
	{
		*size = -1;

		return nullptr;
	}

	*size = it->second.size();

	return it->second.data();
})" << std::endl;
	}
}
