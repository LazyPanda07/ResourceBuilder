cmake_minimum_required(VERSION 3.10.0)

project(resource_builder)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILER_NAME Clang)
    set(CMAKE_CXX_FLAGS -std=c++11)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_NAME G++)
    set(CMAKE_CXX_FLAGS -std=c++11)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER_NAME cl)
    set(CMAKE_CXX_FLAGS /EHsc)
endif()

set(SOURCES main.cpp)

file(GLOB FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
foreach(SOURCE ${FILES})
    set(SOURCES ${SOURCES} ${SOURCE})
endforeach()

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(resource_builder_implementation_library CONFIG)

target_link_libraries(${PROJECT_NAME} PRIVATE resource_builder_implementation_library)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

if (WIN32)
    add_definitions(-DWINDOWS)

    file(COPY ${CMAKE_SOURCE_DIR}/scripts/windows_default_build.bat DESTINATION ${PROJECT_BINARY_DIR})
elseif(UNIX)
    add_definitions(-DLINUX)

    file(COPY ${CMAKE_SOURCE_DIR}/scripts/linux_default_build.sh DESTINATION ${PROJECT_BINARY_DIR})
endif()

file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${PROJECT_BINARY_DIR})
