### Introduction

Game Engine Project. Started as a port from a small Java 2D game engine, turned into a 
3D engine in C++ OpenGL/Vulkan

### Compilation

#### Win32
##### Prerequisites - Tools
* [CMake](https://cmake.org/download/) - Release 3.17 min
* [MinGW](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download) - 8.1.0. Settings in installation should not impact engine
* [Git](https://git-scm.com/download/win) - For Submodules. Might not be required 
* [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) - Latest Windows SDK ( 1.2.170.0 )
* Vulkan GPU Drivers
    * [NVidia](https://developer.nvidia.com/vulkan-driver)
    * [AMD](https://www.amd.com/en/support) - Should be installed by default
    * [AMD](https://github.com/GPUOpen-Drivers/AMDVLK) - Open Source Alternative

##### Prerequisites - Tool Configuration
* User/System PATH variable must contain \<CMake install directory path\>/bin
* User/System PATH variable must contain \<MinGW install directory path\>/bin 
* User/System PATH variable must contain \<Vulkan SDK install directory path\>/\<version\>/bin
* User/System variable must exist : VULKAN_SDK. 
* User/System VULKAN_SDK variable must be \<Vulkan SDK install directory path\>/\<version\>
* Optional. User/System PATH variable must contain \<Git install directory path\>/\<cmd\>

##### Prerequisites - Tool Test
In CMD / Powershell / Windows Terminal
* Command "gcc --version" must output the installed MinGW version
  * Check MinGW installation if NOK
* Command "cmake --version" must output the installed CMake version
  * Check CMake installation if NOK
* Command "vkcube" must run and start a graphical application containing a spinning 3D cube textured with the LunarG logo
  * Check VulkanSDK installation if no command found
  * Restart Computer if application crashed  
  * Check Vulkan Drivers if application renders invalid results ( i.e. no texture / crash after restart )
* Optional - Command "git --version" must output the installed git version
  * Check git installation if NOK
    
#### Project Configuration

Use CMake compatible IDE and build & run target vkTriangle 
  * CLion - CMake Support out of the box. Must configure toolchain to be MinGW ( installed )
  * Visual Studio Code - With CMake Tools extension ( auto configure for project, select MinGW compiler ).
  * CodeBlocks - CMake Support, Select MinGW toolchain
  * Visual Studio - Open CMake Project. Configure CMake to use MinGW

##### OR

In desired directory:

Template:
<pre>
git clone https://github.com/LoghinVladDev/c-eng --recurse-submodules
cd c-eng
mkdir (build-dir)
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" . -B ./(build-dir)/
cmake --build ./(build-dir)/ --target (target-name) -- -j (thread-count)
</pre>

Arguments: 
    * build-dir - directory for output
    * target-name - name of build target. vkTriangle is default
    * thread-count - number of threads used in build

Example: Building target vkTriangle in directory build with 6 threads
<pre>
git clone https://github.com/LoghinVladDev/c-eng --recurse-submodules
cd c-eng
mkdir build
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" . -B ./build/
cmake --build ./build/ --target vkTriangle -- -j 6
</pre>

Multithreading is encouraged in build

Executable will be in output directory, named after the target
Target must be run from the build directory, paths not fully configures
<pre>

cd ./(build-dir)
./(target-name).exe

example : 
cd build
./vkTriangle.exe
</pre>

### Usage

Documentation TBA at a much later date

### Contributing

Contribution guide TBA 

### Dependencies 

CMake 3.5 or later\
Dependencies located in dependencies folder : 

 * [GLFW](https://github.com/glfw/glfw) GLFW framework for OpenGL
 * [GLAD](https://github.com/Dav1dde/glad) OpenGL loader/generator. No longer used
 * [GLM](https://github.com/g-truc/glm) OpenGL mathematics
 * [Open Asset Import Library (assimp)](https://github.com/assimp/assimp) for asset import. Not used
 * [stb\_image](https://github.com/nothings/stb) for texture image loading
