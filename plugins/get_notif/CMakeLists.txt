set (PLUGIN_NAME get_notif)

set(PROJECT_DEBUG_FLAGS "-g")
set(PROJECT_LINKER_FLAGS "-shared")
set(PROJECT_SOURCE_FLAGS "-fpic -ansi -std=c99 -pedantic -Wall")
set(CMAKE_C_FLAGS " \
    ${PROJECT_DEBUG_FLAGS} \
    ${PROJECT_SOURCE_FLAGS} \
    ${PROJECT_LINKER_FLAGS} \
")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/synergy/plugins)

# The plugin should always export a single binary with a .so extension
add_executable (${PLUGIN_NAME} plugin.c)
