# Interstellar Engine
Insterstellar Engine is a game engine with the objective of providing accurate gravitational simulations.
The engine is written in C++20, renders using the Vulkan API, and uses Premake. 

## Building 
Currently the build system only was tested on windows visual studio 2022, anything else is untested and maybe will work, or need tweaking.
One Prerequisite is that the Vulkan SDK is installed, when the script run it will try to fine the Vulkan SDK using the enviroment variable VULKAN_SDK, that point to the Vulkan SDK path, create the variable if it doesn't exist in your system, or if its named something else just change the variable name in the system or int the `BuilPremake.lua` file, or just put vulkan SDK path instead of the variable in the script.
In the root directory open `Premake\Scripts` run the `RunPremake.bat` tha will run premake using the `BuilPremake.lua` once again windows only for visual studio 2022, for other systems see the premake documentation.

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
Making the engine exist, there is nothing currently,

adding build support to more systems
