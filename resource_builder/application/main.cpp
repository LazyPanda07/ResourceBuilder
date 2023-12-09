#include <iostream>

#include "utils.h"
#include "ResourceFileGenerator.h"

/**
 * @param argv <cl, gcc|g++, clang>, output path, <--keep, --ignore_resource_error> || resource paths
 */
int main(int argc, char** argv) try
{
	std::cout << "Usage: <cl, gcc|g++, clang>, output path, <--keep, --ignore_resource_error> || resource paths" << std::endl <<
		"keep - keep generated " + resource_builder::ResourceFileGenerator::resourceFileName + " file" << std::endl <<
		"ignore_resource_error - ignore wrong resource path" << std::endl;

	if (argc < 4)
	{
		std::cout << "Compiler, output path and resource path must be specified" << std::endl;

		return -1;
	}

	resource_builder::ResourceFileGenerator resourceFileGenerator(argc - 3, argv + 3);
	std::unique_ptr<resource_builder::BaseCompilerParameters> parameters =  resource_builder::utils::createParameters(argv[1]);
	bool keep = false;
	
	resourceFileGenerator.createResourceFile(keep);

	std::string command = resource_builder::utils::createResourceCommand(parameters, argv[2]);

	if (system(command.data()))
	{
		throw std::runtime_error("Can't execute command: " + command);
	}

	if (!keep)
	{
		if (remove(resource_builder::ResourceFileGenerator::resourceFileName.data()))
		{
			throw std::runtime_error("Can't remove file: " + resource_builder::ResourceFileGenerator::resourceFileName);
		}
	}

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;

	return -1;
}
