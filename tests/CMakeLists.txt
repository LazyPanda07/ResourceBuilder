cmake_minimum_required(VERSION 3.10)

project(resource_builder_tests)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/resource_builder/core/include)

target_link_libraries(${PROJECT_NAME} PRIVATE resource_builder_core)
