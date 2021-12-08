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
|L Shift|Move Faster|
|Space|Randomize Light Color|
|C|Reset Light Color|
|Mouse Scroll|Camera Zoom|
|X|Reset Camera Zoom|

# Running the Program
To run the program, first navigate to the releases tab or [click here](https://github.com/LensPlaysGames/CMake_OpenGLBasics/releases). \
Identify a built version of the program for your OS, and download the compressed archive.

Once downloaded, extract the archive to a folder and run the program how you normally would on your OS.

For example, On Windows (Win64) this entails navigating to the `Releases` directory and running the `.exe` within it.

If a release has not been built for your OS, you can always [build it yourself](https://github.com/LensPlaysGames/CMake_OpenGLBasics#building-the-program).

## Building the Program
This will outline how to build the project using command line. \
If you are using a GUI, it's likely not all of the functionality is present (for example in GitHub Desktop, submodule functionality is not supported, so command line is necessary).

### 1.) Clone Repository

Navigate to the directory you would like the cloned repository to reside in. Take note that the clone will be in a subfolder. \
`cd Path/To/Where/Repository/Will/Be/Cloned/To`

Once within the correct directory, clone this repository to it using the following git command: \
`git clone --recursive https://github.com/LensPlaysGames/CMake_OpenGLBasics` \
The `--recursive` tells git to also download all necessary submodules.

This may take a while, so be patient. \

To double-check the submodules are included correctly, use a file explorer and make sure the directories of the submodules contain more than just a `.git` file. 

If the folders are empty, there are a few things you can try seen below. \
If the folders are populated correctly, [skip to Step 2 - Build with CMake](https://github.com/LensPlaysGames/CMake_OpenGLBasics#2-build-with-cmake).

The following commands are ran from inside the cloned repository directory. \
If using the same git terminal as before, you will need to navigate to the cloned directory. \
`cd CMake_OpenGLBasics`

Some people have had success using the following commands: \
`git submodule sync` \
`git submodule update --init`
 
If the submodule's directories are still empty, run the following commands: \
`git submodule init` \
`git submodule update`

One common error I get is 'fatal: Needed a single revision'. \
To solve this, I found this [StackOverflow thread](https://stackoverflow.com/questions/38227598/git-submodule-update-init-gives-error-fatal-needed-a-single-revision-unable-t).

If you're not into reading, or the thread is deleted by now, you can try to run the following commands before running submodule init and submodule update once again. \
`git submodule foreach git pull origin master` \
This command should try to download the submodule repository from origin master, which is the default repository branch.

If for some reason, git still won't pull the submodule's repository to your machine, you can always do it yourself by cloning the repository directly. \
`git clone https://github.com/Perlmint/glew-cmake` \
`git clone https://github.com/glfw/glfw` \
`git clone https://github.com/g-truc/glm` \
`git clone https://github.com/assimp/assimp` \
Make sure to delete the existing empty directory before running the clone command or git will complain.

These commands should download and update all submodules if the `--recursive` tag didn't work when cloning. \
If the tag did work, nothing will change.

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

Included is a `build_cmake.bat` file that can be ran to build the program using the default CMake generator for your system.

For Windows, the default generator is Visual Studio 17 2022, which is exactly what I use. \
That means to generate a solution, all one has to do is double click the `.bat`. \
From there, you can build the solution in Visual Studio to get a `.exe` to run.

For Linux, the default generator is Makefile, or just Make. \
That means, once you run `sh build_cmake.bat`, navigate to the build directory and run `make`. \
This will generate a file that may be executed successfully. 

For further instructions, find your specific platform/generator below!

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
Once the solution is open, select the correct build target configuration with the dropdown at the top (default is "Debug" but "Release" has much better performance). \
Once the target is set correctly, build the solution. This can be done using `F6` or through the Build dropdown at the top. \
Beware, this may take several minutes! I recommend getting up and stretching, using the restroom, or even just drinking some water. \
If all goes well, you will end up with a .exe in the 'OpenGLBasics/Release' directory. Run this to run the program.

### For Linux (using Make):
Ensure you have updated and upgraded all packages by running \
`apt update` \
then \
`apt upgrade`

Get the latest drivers for your hardware. Seriously, it matters!!!

Linux doesn't natively support OpenGL, so a third-party library is necessary. This guide will use the most common solution: [Mesa](https://mesa3d.org/)

Ensure the following Debian packages are installed!
- build-essential
- mesa-common-dev
- mesa-utils
- libgl-dev
- libglew-dev
- libglm-dev
- libglx-dev
- libopengl-dev
- libx11-dev

One-liner command: \
`apt install build-essential mesa-common-dev mesa-utils libgl-dev libglew-dev libglm-dev libglx-dev libopengl-dev libx11-dev`

To ensure the correct version of OpenGL is supported (V3.30 or later), run the following command: \
`glxinfo | grep version` \
'OpenGl core profile version string' is what you are looking for, although it may be under 'GLX Max core profile version'

Once all necessary packages are installed, open a terminal and navigate to the cloned repository directory (containing CMakeLists.txt) ie. \
`cd Path/To/Where/You/Cloned/The/Repository`

Once in the correct directory, generate a Makefile using the following command: \
`cmake -G "Unix Makefiles" -S . -B ./build` \
or just \
`sh build_cmake.bat`

After CMake is finished building the Makefile, navigate to the CMake build directory and then make the Makefile: \
`cd build` \
`make`

This may take quite some time, especially the first time (however subsequent builds' speed will be greatly increased).

To run the program, execute the generated `CMake_OpenGLBasics` file in the OpenGLBasics directory. \
`./CMake_OpenGLBasics`

**Errors I've encountered:** \
**Error:** "GLX: Failed to create context: GLXBadFBConfig" \
**Solution:** Install required mesa & x11 packages.

**Error:** "OpenGL Version(null)" \
**Solution:** Execute with mesa gl version override \
`MESA_GL_VERSION_OVERRIDE=3.3 ./CMake_OpenGLBasics`

---

If you encounter errors, submit an issue and I will do my best to help you and update this guide with any likely speed-bumps along the way.
