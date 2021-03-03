### For Game Design 2021 - UAIC FII 

Project Proposal and technical specs : 
[document](https://github.com/LoghinVladDev/c-eng/blob/master/GD_Loghin_Vlad-Andrei_Engine_ProjectProposal.docx) Project Proposal

### Introduction

Game Engine Project. Started as a port from a small Java 2D game engine, turned into a 
3D engine in C++ OpenGL/Vulkan

## Compilation

### Prerequisites - Tools
#### Win32
* [CMake](https://cmake.org/download/) - Release 3.16 min
* [MinGW(recommended)/MSVC](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download) - 8.1.0. Settings in installation should not impact engine / MSVC with Visual Studio 2019 16.9. 
* [Git](https://git-scm.com/download/win) - For Submodules. Might not be required 
* [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) - Latest Windows SDK ( 1.2.170.0 )
* Vulkan GPU Drivers
    * [NVidia](https://developer.nvidia.com/vulkan-driver)
    * [AMD](https://www.amd.com/en/support) - Should be installed by default
    * [AMD](https://github.com/GPUOpen-Drivers/AMDVLK) - Open Source Alternative
#### Linux - Ubuntu
* CMake
* GCC
<pre>
sudo apt-get install cmake
sudo apt-get install gcc g++
</pre>
* GCC-10 - Optional, but highly preferred - sudo apt-get install gcc-10 g++-10
<pre>
sudo apt-get install gcc-10 g++-10
</pre>
* Vulkan SDK 
* Option 1 : Pre-Built Binaries for Distribution - Will install latest pre-built vulkan version. Will not be the latest version, project might not run.
<pre>
sudo apt-get install vulkan-tools
sudo apt-get install libvulkan-dev
sudo apt-get install vulkan-validationlayers-dev spirv-tools
</pre>
* Option 2 : Build Vulkan Binaries
System Update
<pre>
sudo apt-get update
sudo apt-get dist-upgrade
</pre>

Build tools for vulkanSDK
<pre>
sudo apt-get install libglm-dev cmake libxcb-dri3-0 libxcb-present0 libpciaccess0 \
libpng-dev libxcb-keysyms1-dev libxcb-dri3-dev libx11-dev g++ gcc g++-multilib \
libmirclient-dev libwayland-dev libxrandr-dev libxcb-ewmh-dev git python3 bison
</pre>

Build tools for vulkanConfigurator
<pre>
sudo apt-get install qt5-default qtwebengine5-dev
</pre>

Download latest Linux Vulkan SDK Tarball [here](https://vulkan.lunarg.com/sdk/home)

Extract it to /your/desired/path/vulkan/1.2.xxx.y

### Prerequisites - Tool Configuration

#### Win32

* User/System PATH variable must contain \<CMake install directory path\>/bin
* User/System PATH variable must contain \<MinGW install directory path\>/bin 
* User/System PATH variable must contain \<Vulkan SDK install directory path\>/\<version\>/bin
* User/System variable must exist : VULKAN_SDK. 
* User/System VULKAN_SDK variable must be \<Vulkan SDK install directory path\>/\<version\>
* Optional. User/System PATH variable must contain \<Git install directory path\>/\<cmd\>

#### Linux
* Vulkan SDK Config (A or B):
* A: export variables to current session
<pre>
source /your/desired/path/vulkan/1.2.xxx.y/setup-env.sh
</pre>
OR 
<pre>
export VULKAN_SDK=your/desired/path/vulkan/1.1.xx.y/x86_64
export PATH=$VULKAN_SDK/bin:$PATH
export LD_LIBRARY_PATH=$VULKAN_SDK/lib:$LD_LIBRARY_PATH
export VK_LAYER_PATH=$VULKAN_SDK/etc/vulkan/explicit_layer.d
</pre>
* B: Add the source command/exports into your terminal environment startup script 
    * i.e. ~/.bashrc
    
A restart is recommended at this step, but not mandatory. If crashes occur later on, restart

#### 

### Prerequisites - Tool Test

#### Win32
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
    
#### Linux
In terminal
* "cmake --version" displays cmake version higher than 3.16
* "gcc --version" displays version higher than 9.3 (initial c++2a support)
* "g++ --version" does the same
* "git --version" displays valid version
* "vkcube" starts and displays a spinning 3d rendered cube textured with the LunarG logo. If crash is encountered (segmentation fault), restart. If it still crashes, use pre-build binaries

### Project Configuration - Cross Platform

Project Clone: 

Clone through git bash / cmd / terminal, or any git client.\
<strong>!!! Make sure to use recursive cloning. (--recurse-submodules) !!!\
Or run git submodule update --init after clone. Otherwise, build will fail</strong>

<pre>
git clone https://github.com/LoghinVladDev/c-eng --recurse-submodules
</pre>

Open Directory in CMake compatible IDE and build & run target vkTriangle 
  * CLion - CMake Support out of the box. Must configure toolchain to be MinGW ( installed )
  * Visual Studio Code - With CMake Tools extension ( auto configure for project, select MinGW compiler ).
  * CodeBlocks - CMake Support, Select MinGW toolchain
  * Visual Studio - Open CMake Project. Configure CMake to use MinGW

#### OR

Build commands to run from 'c-eng' directory:

Template:
<pre>
mkdir (build-dir)
cmake -DCMAKE_BUILD_TYPE=Debug [-G "generator-name" ] . -B ./(build-dir)/
cmake --build ./(build-dir)/ --target (target-name) -- -j (thread-count)
</pre>

Arguments: 
* build-dir - directory for output
* target-name - name of build target. vkTriangle is default
* thread-count - number of threads used in build
* generator-name - name of the compiler configurator. 
    * win32 : use "MinGW Makefiles" | leave empty for MVSC
    * linux : if using gcc, leave empty

#### Example: Win32 Building target vkTriangle with MinGW in directory build with 6 threads
<pre>
mkdir build
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" . -B ./build/
cmake --build ./build/ --target vkTriangle -- -j 6
</pre>

#### Example: Linux Building target vkTriangle in directory build with 6 threads
<pre>
mkdir cmake-build
cmake -DCMAKE_BUILD_TYPE=Debug . -B ./cmake-build/
cmake --build ./cmake-build/ --target vkTriangle -- -j 6
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
