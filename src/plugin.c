#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>

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
    strcat(plugin_path, ".so");
    printf("%s\n", plugin_path);

    /* open the plugin */
    void *handle = dlopen(plugin_path, RTLD_NOW);
    if (!handle) {
        printf("Fuck\n");
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

    /* run the plugin init function */
    (*plugin_init_func)();

    printf("Loaded plugins: %s\n", plugin_name);
    return 1;
}
