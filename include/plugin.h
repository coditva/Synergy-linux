#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

/* load a plugin given by plugin name */
int plugin_load(const char *plugin_name);

/* discover all plugins in the plugins folder */
void plugin_discover();

#endif /* end of include guard: PLUGIN_MANAGER_H */
