# Specify a minimum version
cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

# Specify project name
project (synergy-linux C)

# Set version numbers
set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 0)
set (PROJECT_VERSION_PATCH 1)

# Set directories
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/synergy)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/synergy)

# Add included directories
include_directories("${PROJECT_SOURCE_DIR}/include")

# Add compiler flags
set(PROJECT_DEBUG_FLAGS "-g")
set(PROJECT_LINKER_FLAGS "-ldl")
set(PROJECT_SOURCE_FLAGS "-ansi -std=c99 -pedantic -Wall")
set(CMAKE_C_FLAGS " \
    ${PROJECT_DEBUG_FLAGS} \
    ${PROJECT_SOURCE_FLAGS} \
    ${PROJECT_LINKER_FLAGS} \
")

# Setup list of source files
set(PROJECT_SOURCES
    src/main.c
    src/server.c
    src/device.c
    src/plugin.c
)

# Add subdirectory for plugins
add_subdirectory("plugins")

# Add executable
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LINKER_FLAGS})
