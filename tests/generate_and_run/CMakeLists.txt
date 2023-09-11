cmake_minimum_required(VERSION 3.10)

add_executable(generate_and_run main.cpp)

if (UNIX)
    target_link_libraries(generate_and_run dl)
endif()
