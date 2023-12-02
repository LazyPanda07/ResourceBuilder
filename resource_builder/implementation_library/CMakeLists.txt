cmake_minimum_required(VERSION 3.10.0)

project(resource_builder_implementation_library)

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
endif()
