cmake_minimum_required(VERSION 3.10.0)

project(resource_builder)

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
