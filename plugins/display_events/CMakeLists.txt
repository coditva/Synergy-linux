set (PLUGIN_NAME display_events)

set(PROJECT_DEBUG_FLAGS "-g")
set(PROJECT_LINKER_FLAGS "-shared -lnotify")
set(PROJECT_SOURCE_FLAGS "-fpic -ansi -std=c99 -pedantic -Wall")
set(CMAKE_C_FLAGS " \
    ${PROJECT_DEBUG_FLAGS} \
    ${PROJECT_SOURCE_FLAGS} \
    ${PROJECT_LINKER_FLAGS} \
")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/synergy/plugins)

# pkgconfig needed for libnotify
find_package(PkgConfig REQUIRED)
pkg_search_module(LIBNOTIFY REQUIRED libnotify)

# The plugin should always export a single binary with a .so extension
add_executable (${PLUGIN_NAME} plugin.c)

# add the libnotify libraries
target_link_libraries(${PLUGIN_NAME} ${LIBNOTIFY_LIBRARIES})
target_include_directories(${PLUGIN_NAME} PUBLIC ${LIBNOTIFY_INCLUDE_DIRS})
target_compile_options(${PLUGIN_NAME} PUBLIC ${LIBNOTIFY_CFLAGS_OTHER})
