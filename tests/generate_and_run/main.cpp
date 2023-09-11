#include <iostream>
#include <vector>
#include <algorithm>

#ifdef LINUX
#include <dlfcn.h>
#elif WINDOWS
#include <Windows.h>
#endif

using signature = const std::vector<uint8_t>& (*)(const std::string&);

int main(int argc, char** argv)
{
    std::string projectPath = argv[1];
#ifdef WINDOWS
    projectPath += ".exe";
#endif
    std::string buildPath = argv[2];
#ifdef LINUX
    buildPath += "/default.so";
#elif WINDOWS
    buildPath += "/default.dll";
#endif 
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
#ifdef LINUX
            void* handle = dlopen(buildPath.data(), RTLD_LAZY);
#elif WINDOWS
            HMODULE handle = LoadLibraryA(buildPath.data());
#endif
            if (handle)
            {
#ifdef LINUX
                signature ptr = reinterpret_cast<signature>(dlsym(handle, "getResource"));
#elif WINDOWS
                signature ptr = reinterpret_cast<signature>(GetProcAddress(handle, "getResource"));
#endif
                if (ptr)
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

            return 4;
        }

        return 0;
}
