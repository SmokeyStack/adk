# Add-on Development Kit

This Add-on Development Kit allows you to create add-ons without writing JSON! It is similar to Forge's MDK for Minecraft: Java Edition

## Installing ADK

- Install [Regolith](https://bedrock-oss.github.io/regolith/guide/installing)
- Install [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022)
- Install [Vcpkg](https://github.com/microsoft/vcpkg) and set up command line integration as described in the Vcpkg docs. Remember the location of Vcpkg's `CMAKE_TOOLCHAIN_FILE`
- Run `vcpkg install spdlog:x64-windows`
- Install [CMake](https://cmake.org/install/)
- Run `regolith init` in your directory of choice
- Run `regolith install adk`
- Open the directory in your choice of IDE

\*Note, as of now, `manifest.json` needs to be created manually

## How to use

See [filter directory](adk/data) to see the example
