cmake_minimum_required(VERSION 3.10.0)

project(resource_builder)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS -std=c++11)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS -std=c++11)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS /EHsc)
endif()

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE resource_builder_implementation_library)

if (WIN32)
    add_definitions(-DWINDOWS)

    file(COPY ${CMAKE_SOURCE_DIR}/scripts/windows_default_build.bat DESTINATION ${PROJECT_BINARY_DIR})
elseif(UNIX)
    add_definitions(-DLINUX)

    file(COPY ${CMAKE_SOURCE_DIR}/scripts/linux_default_build.sh DESTINATION ${PROJECT_BINARY_DIR})
endif()

file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${PROJECT_BINARY_DIR})
