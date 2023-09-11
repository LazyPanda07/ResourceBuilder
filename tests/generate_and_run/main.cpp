#include <iostream>
#include <vector>
#include <algorithm>

#include <dlfcn.h>

using signature = const std::vector<uint8_t>& (*)(const std::string&);

int main(int argc, char** argv)
{
    std::string projectPath = argv[1];
    std::string buildPath = std::string(argv[2]) + "/default.so";
    std::string compiler = [argv]() 
    {
        std::string result = argv[3];
        
        std::for_each(result.begin(), result.end(), [](char& c) { c = tolower(c); }); 

        return result; 
    }();
    std::string command = projectPath + ' ' + compiler + " default --keep default.jpg";

    if (system(command.data()))
    {
        return 1;
    }

    try
    {
        if (void* handle = dlopen(buildPath.data(), RTLD_LAZY))
        {
            if (signature ptr = reinterpret_cast<signature>(dlsym(handle, "getResource")))
            {
                return ptr("default.jpg").empty();
            }
            else
            {
                return 3;
            }
        }
        else
        {
            return 2;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;

        return -4;
    }

    return 0;
}
