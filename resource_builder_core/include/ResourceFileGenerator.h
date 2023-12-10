#pragma once

#include <string>
#include <fstream>

namespace resource_builder
{
	class ResourceFileGenerator
	{
	public:
		static const std::string resourceFileName;

	private:
		int argc;
		char** argv;

	private:
		static void generateHeaders(std::ofstream& resourceFile);

	public:
		ResourceFileGenerator(int argc, char** argv);

		void createResourceFile(bool& keep) const;

		~ResourceFileGenerator() = default;
	};
}
