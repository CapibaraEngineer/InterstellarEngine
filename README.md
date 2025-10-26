# Interstellar Engine
![Static Badge](https://img.shields.io/badge/Version-PRE--ALPHA%2094-blue)

Insterstellar Engine is a game engine with the objective of doing something and looking cool.
The engine is written in C++23, renders using the Vulkan API, and uses Premake. 

## Building 

Currently the build system only was tested on Windows Visual Studio 2022 and 2026, if you plan on using VS2026 and if you donwload premake5.0-beta7 (the most recent verison when I am writing this, by beta8 this probaly will be fixed) you will need to run premake configured for VS2022 because it doens't yet support VS2026, when you open the solution VS you will prompt you that the version is old or sometinhg, you just tell him to use the most recent one. I tried running it with Linux GCC 15.2, you will need to tweak it a lot, and I couldn't figure out how to make C++20 modules work. Anything else is untested and maybe will work, or need tweaking.
In the root directory open `Premake\Scripts` run the `RunPremake.bat` that will run premake using the `BuilPremake.lua` this batch file is only for Windows and Visual Studio 2022, for other systems see the premake documentation.

One Prerequisite is that the Vulkan SDK is installed, when the script run it will try to find the Vulkan SDK using the enviroment variable `VULKAN_SDK`, that variable points to the Vulkan SDK path, if you have problems with it, you can solve in a few ways: 
1. Create the variable if it doesn't exist in your system;
2. If its named something else just change the variable name in the system, or the variable name in the `BuilPremake.lua` file;
3. or just put vulkan SDK path instead of the variable in the `BuilPremake.lua` file.
   
## Contributing
You are free to contribute to the project, see the [contributing guideline here](https://github.com/CapibaraEngineer/InterstellarEngine/blob/master/CONTRIBUTING.md).

## Planned things
1.Making the engine exist, it now renders 3d things

2.adding build support to more systems
