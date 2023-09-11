cmake_minimum_required(VERSION 3.10.0)

project(resource_builder)

set(CMAKE_CXX_FLAGS -std=c++11)

include(CTest)

set(SOURCES main.cpp)

file(GLOB FILES ${CMAKE_SOURCE_DIR}/source/*.cpp)
foreach(SOURCE ${FILES})
    set(SOURCES ${SOURCES} ${SOURCE})
endforeach()

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

if (WIN32)
    add_definitions(-DWINDOWS)

    file(COPY ${CMAKE_SOURCE_DIR}/scripts/windows_default_build.bat DESTINATION ${CMAKE_BINARY_DIR})
elseif(UNIX)
    add_definitions(-DLINUX)

    file(COPY ${CMAKE_SOURCE_DIR}/scripts/linux_default_build.sh DESTINATION ${CMAKE_BINARY_DIR})
endif()

file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(tests)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILER_NAME Clang)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_NAME G++)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER_NAME Cl)
endif()

add_test(NAME GenerateAndRun${COMPILER_NAME} COMMAND generate_and_run ${CMAKE_BINARY_DIR}/${PROJECT_NAME} ${CMAKE_BINARY_DIR} ${COMPILER_NAME})
