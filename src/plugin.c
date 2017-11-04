#include <stdio.h>
#include <dlfcn.h>

#include "plugin.h"
#include "datatypes.h"

int plugin_load(const char *plugin_name)
{
    void *handle = dlopen("synergy/plugins/get_notif.so", RTLD_NOW);
    if (!handle) {
        printf("Fuck\n");
        return 1;
    }
    init_func_t plugin_init_func = (init_func_t) (__intptr_t) dlsym(handle, "plugin_get_notif_init");
    plugin_init_func();
    printf("Loaded plugins: %s\n", plugin_name);
    return 1;
}
