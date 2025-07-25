# Interstellar Engine
Insterstellar Engine is a game engine with the objective of providing accurate gravitational simulations.
The engine is written in C++23, renders using the Vulkan API, and uses Premake. 

## Building 

Currently the build system only was tested on windows visual studio 2022, anything else is untested and maybe will work, or need tweaking.
In the root directory open `Premake\Scripts` run the `RunPremake.bat` that will run premake using the `BuilPremake.lua` this batch file is only for  windows and visual studio 2022, for other systems see the premake documentation.

One Prerequisite is that the Vulkan SDK is installed, when the script run it will try to find the Vulkan SDK using the enviroment variable `VULKAN_SDK`, that variable points to the Vulkan SDK path, if you have problems with it, you can solve in a few ways: 
1. Create the variable if it doesn't exist in your system;
2. If its named something else just change the variable name in the system, or the variable name in the `BuilPremake.lua` file;
3. or just put vulkan SDK path instead of the variable in the `BuilPremake.lua` file.
   
## Contributing
You are free to contribute to the project, see the [contributing guideline here](https://github.com/CapibaraEngineer/InterstellarEngine/blob/master/CONTRIBUTING.md).

## Planned things
1.Making the engine exist, it now renders 3d things

2.adding build support to more systems
