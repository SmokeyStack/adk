# Add-on Development Kit

This Add-on Development Kit is essentially just me messing around with ways to create add-ons for Minecraft without touching JSON. It also uses Regolith to export the files to the Minecraft Directory.

## Installing ADK
Download it from the latest release

## Creating Add-ons
- Install Regolith
- Install Visual Studio Build Tools
- Run `regolith init` in your directory of choice
- Extract the zip file downloaded from the latest release
- Open the directory in your choice of IDE
- Create `Main.cpp` and `Datagen.cpp` and paste the following code

Main.cpp
```cpp
#include "Registry.h"

int main() {
    const std::string MODID = "custom_namespace";
    Registry<Block> mod(MODID);

    return 0;
}
```

DataGen.cpp
```cpp
#include "BlockState.h"

int main() {
    return 0;
}
```

- Run `compile.bat` in the terminal to export it to Minecraft

*Note, as of now, `manifest.json` needs to be created manually