# Interstellar Engine
Insterstellar Engine is a game engine with the objective of providing accurate gravitational simulations.
The engine is written in C++20, renders using the Vulkan API, and uses Premake. 

## Building 

Currently the build system only was tested on windows visual studio 2022, anything else is untested and maybe will work, or need tweaking.
In the root directory open `Premake\Scripts` run the `RunPremake.bat` that will run premake using the `BuilPremake.lua` this batch file is only for  windows and visual studio 2022, for other systems see the premake documentation.

One Prerequisite is that the Vulkan SDK is installed, when the script run it will try to find the Vulkan SDK using the enviroment variable `VULKAN_SDK`, that variable points to the Vulkan SDK path, if you have problems with it, you can solve in a few ways: 
1. Create the variable if it doesn't exist in your system;
2. If its named something else just change the variable name in the system, or the variable name in the `BuilPremake.lua` file;
3. or just put vulkan SDK path instead of the variable in the `BuilPremake.lua` file.
   


## Contributing

### Bug reports e feature suggestion
If you found a bug report it a the github issue tracker, but before check if anyone already reported it, please give the most information you can on the bug.

Before opening a new  feature request, use the search feature at the top of that page to see if it has already been requested;
Explain the problem that you're having, and anything you've tried to solve it using the currently available features;
Explain how this new feature will help;
If possible, provide an example, like a code snippet, showing what your new feature might look like in use.

### Pull Requests
if you fixed a bug or added a feature create a pull request

If you haven't already, create a fork of the Premake repository;
Create a topic branch, and make all of your changes on that branch;
Submit a pull request, and wait;
it will be reviewed and if it is good merged.

### Coding conventions:
Use camelCase, 
use tabs for indentation, not spaces,
when in doubt, match the code that's already there.

## Planned things
1.Making the engine exist, well, now there's something, some debug messages along with the blank window, but it still doens't renders anything

2.adding build support to more systems
