cmake_minimum_required(VERSION 3.10.0)

project(resource_builder_core)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS -std=c++11)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS -std=c++11)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS /EHsc)
endif()

file(GLOB FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
foreach(SOURCE ${FILES})
    set(SOURCES ${SOURCES} ${SOURCE})
endforeach()

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

if (WIN32)
    add_definitions(-DWINDOWS)
elseif(UNIX)
    add_definitions(-DLINUX)

    target_link_libraries(${PROJECT_NAME} PRIVATE -static)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
