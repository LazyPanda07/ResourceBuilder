cmake_minimum_required(VERSION 3.10.0)

project(resource_builder_solution)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/make_install)

add_subdirectory(resource_builder_core)

add_subdirectory(resource_builder)
