# Object Oriented Programming in OpenGL  
Written in C++ using shaders written in GLSL.

Load 3D Models from nearly any file type, and visualize it in a 3D space **lit in real time!** \
Position, rotate, and scale objects for nearly **endless fun!** \
90s commercial generic excited phrase to get you **pumped!**

## Controls
|**Key**|**Action**|
|:---:|---|
|WASD|Move|
|Q|Move Up|
|E|Move Down|
|Space|Randomize Light Color|
|C|Reset Light Color|

## Building the Program
### 1.) Clone Repository
This can be done with the following git command: \
`git clone --recursive https://github.com/LensPlaysGames/CMake_OpenGLBasics` \
The `--recursive` tells git to also download all necessary submodules.

Once everything is cloned over to your local repository, run the following commands: \
`git submodule init` \
`git submodule update`

This may take a while, so be patient. \
These commands should download and update all submodules if the `--recursive` tag didn't work when cloning (which it never does for me). \
If the tag did work, nothing will change.

To double-check the submodules are correctly initialized and updated, use the git command: \
`git submodule status`

This will return what looks like a bunch of nonsense but if all of the submodules listed below are listed there then you are good to go. \
Example of correct console output: \
`$ git submodule status` \
 `70f5cca9c3ebd84b89c5775852ac9aa2449f6c5b assimp (Release3.1_RC1-8864-g70f5cca9c)` \
 `466859eeea029099db5b342a506e68d3ea3b78a7 glew-cmake (glew-1.10.0-716-g466859e)` \
 `53d86c64d709ff52886580d338d9b3b2b1f27266 glfw (3.3-505-g53d86c64)` \
 `6ad79aae3eb5bf809c30bf1168171e9e55857e45 glm (0.9.5.3-2659-g6ad79aae)`

Once common error I get is 'fatal: Needed a single revision'. \
To solve this, I found this [StackOverflow Thread](https://stackoverflow.com/questions/38227598/git-submodule-update-init-gives-error-fatal-needed-a-single-revision-unable-t) \
If you're not into reading, or the thread is deleted by now, you can try to run the following commands before running submodule init and submodule update once again. \
`git submodule foreach git pull origin master`

This command should try to download the submodule repository from origin master, which is the default repository branch.

Some poeple have had success using the following commands: \
`git submodule sync` \
`git submodule update --init`

If for some reason, git still won't pull the submodule's repository to your machine, you can always do it yourself by cloning the repository directly. \
`git clone https://github.com/Perlmint/glew-cmake` \
`git clone https://github.com/glfw/glfw` \
`git clone https://github.com/g-truc/glm` \
`git clone https://github.com/assimp/assimp` \
Make sure to delete the existing empty directory before running the clone command or git will complain.

### Submodules:
(in case you are having trouble cloning correctly)
- [GLEW](https://github.com/Perlmint/glew-cmake)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [ASSIMP](https://github.com/assimp/assimp)

## 2.) Build with CMake
**Ensure CMake V3.22 or newer is installed on your system!**

CMake is a cross-platform, [open-source](https://github.com/Kitware/CMake) build system generator. 

For full documentation visit the [CMake Home Page](https://cmake.org/) and the [CMake Documentation Page](https://cmake.org/documentation). \
The [CMake Community Wiki](https://gitlab.kitware.com/cmake/community/-/wikis/home) also references useful guides and recipes.

This will outline how to build the project using command line, so if you are using a GUI feel free to submit an issue and I will do my best to help you out.

First, determine which build system generator of CMake you would like to use. \
Build system generators are **platform specific**, so be sure to choose the correct one for your environment. \
For a list of available generators, reference the [CMake Documentation Page](https://cmake.org/documentation). \
Alternatively, run the following command in a terminal: \
`cmake --help`

### For Visual Studio 17 2022:
Open a terminal and navigate to the cloned repository directory (containing CMakeLists.txt) ie. \
`cd Path/To/Where/You/Cloned/The/Repository`

Once in the correct directory, generate a solution and project using the following command: \
`cmake -G "Visual Studio 17 2022" -S . -B ./build`

Feel free to replace `./build` with any output directory of your choice.

Once built, navigate to the build directory and open up the Visual Studio solution (be sure to open with the correct version of Visual Studio). \
Once the solution is open, select the correct build target (default is "Debug" but "Release" has much better performance). \
Once the target is set correctly, build the solution. This can be done quickly using `F6` or through the Build dropdown at the top. \
If all goes well, you will end up with a .exe in the 'OpenGLBasics' directory. Run this to run the program.
