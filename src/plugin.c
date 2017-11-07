#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "plugin.h"
#include "datatypes.h"

/*
 * Loads the plugin code and runs the init function for it
 * @param const char * the plugin to be loaded
 * @return int 1 if plugin loaded, 0 if not
 */
int plugin_load(const char *plugin_name)
{
    char *plugin_path;
    char *function_name;

    /* compute the plugin path */
    plugin_path = (char *) malloc(sizeof("synergy/plugins/.so") + sizeof(plugin_name));
    strcpy(plugin_path, "synergy/plugins/");
    strcat(plugin_path, plugin_name);

    /* open the plugin */
    void *handle = dlopen(plugin_path, RTLD_NOW);
    if (!handle) {
        printf("Could not load plugin: %s\n", plugin_name);
        return 0;
    }

    /* compute plugin init function path */
    function_name = (char *) malloc(sizeof("plugin_init_") + sizeof(plugin_name));
    strcpy(function_name, "plugin_");
    strcat(function_name, plugin_name);
    strcat(function_name, "_init");

    /* get plugin init function address */
    plugin_init_func_t plugin_init_func = (plugin_init_func_t) (__intptr_t)
        dlsym(handle, function_name);

    /* if function address was not found */
    if (plugin_init_func == NULL) {
        printf("Could not load plugin: %s\n", plugin_name);
        return 0;
    }

    /* run the plugin init function */
    (*plugin_init_func)();

    return 1;
}

/*
 * Searches the plugins directory and loads all the plugins it can find
 */
void plugin_discover()
{
    DIR *plugins_dir;
    struct dirent *dir_entry;

    /* open plugins directory */
    if ((plugins_dir = opendir("synergy/plugins")) == NULL) {
        printf("Could not find plugins dir\n");
        return;
    }

    /* load each plugin */
    while ((dir_entry = readdir(plugins_dir)) != NULL) {

        if (strcmp(dir_entry -> d_name, ".") &&
                strcmp(dir_entry -> d_name, "..")) {

            printf("Loading plugin: %s\n", dir_entry -> d_name);
            plugin_load(dir_entry -> d_name);
        }
    }
}
