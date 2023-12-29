# Add-on Development Kit

This Add-on Development Kit(ADK) allows you to create add-ons without writing JSON! It is similar to Forge's MDK for Minecraft: Java Edition

## Usage

ADK can be used in two ways, as a standalone or as a regolith filter. The difference between the two is the way you import ADK and how you export your add-on.
As a standalone, you will need to manually copy the files to your `com.mojang` folder. As a regolith filter, you just need to set up your `config.json` and regolith will do the rest.

## Installing ADK

__**Common Steps**__
- Install [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022)
- Install [CMake](https://cmake.org/install/)
- Install [vcpkg](https://github.com/microsoft/vcpkg) and set up command line integration as described in the Vcpkg docs. Remember the location of vcpkg's `CMAKE_TOOLCHAIN_FILE`
- Run `vcpkg install spdlog:x64-windows`

__**Standalone**__
- Clone this repository
- Copy the contents of the `adk/data` folder to your project

__**Regolith Filter**__
- Install [Regolith](https://bedrock-oss.github.io/regolith/guide/installing)
- Run `regolith init` in your directory of choice
- Run `regolith install adk`

## How to use

After you have installed ADK, you can start creating add-ons. Create a `BP` and `RP` folder in your project directory.
Create your `manifest.json` like you would normally do for any add-on.

### Getting Started

In the `Main.cpp` file, edit the `custom_namespace` to your liking. These will be used as your add-on's namespace.
The main files which you will be using is the `Data.cpp`, `Language.cpp`, `Object.cpp` and `Recipe.cpp` files.

__**What are these files?**__
- `Object.cpp` is where you will be adding your blocks and items.
- `Data.cpp` is where you will be adding your textures to your blocks and items.
- `Recipe.cpp` is where you will be adding your recipes.
- `Language.cpp` is where you will be adding your translations.

See the files in the [data folder](adk/data) for examples.

### Building

__**Standalone**__

- Run `compile-standalone.bat` to build your add-on

__**Regolith Filter**__

- Run `regolith run default`(or whichever profile you're using) to build your add-on

## Third Party Software

This project uses the following third party software:

- [gabime/spdlog](https://github.com/gabime/spdlog)
- [nlohmann/json](https://github.com/nlohmann/json)