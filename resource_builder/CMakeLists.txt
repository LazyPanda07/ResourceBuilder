cmake_minimum_required(VERSION 3.10.0)

project(resource_builder)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/make_install)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS -std=c++11)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS -std=c++11)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS /EHsc)
endif()

add_executable(${PROJECT_NAME} "main.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/resource_builder_core/include)

target_link_libraries(${PROJECT_NAME} PRIVATE resource_builder_core)

if (WIN32)
    add_definitions(-DWINDOWS)

    set(SHELL_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/windows_default_build.bat)
elseif(UNIX)
    add_definitions(-DLINUX)

    set(SHELL_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/linux_default_build.sh)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${SHELL_SCRIPT} DESTINATION ${PROJECT_BINARY_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${SHELL_SCRIPT} DESTINATION ${CMAKE_INSTALL_PREFIX})
