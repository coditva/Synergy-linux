# Synergy-linux
Linux part for the [Synergy Project](https://github.com/UtkarshMe/Synergy)  
Send notifications from phone to Linux desktop with ease.

### Compiling
```bash
mkdir -p build && cd build
cmake ..
make
synergy/synergy-linux #to run
```

### Plugins
- Put plugins in `plugins` folder and use the CMakeLists.txt file to compile
as Shared Objects.
- Each plugin must contain a `plugin_PLUGINNAME_init` function which attaches
a handler for an event.
- See sample plugins for examples

### Author
Utkarsh Maheshwari

### License
GPL version 3
