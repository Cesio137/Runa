# Nanometro

Nanometro (Decimal Metric System) is a set of tools planned to be an open-source, real-time, cross-platform 2D and 3D engine.

## Suported Platforms

---

- [x] Windows

- [ ] Linux(Help Wanted)

- [ ] Mac(Help Wanted)

## Download and Install

---

- [Git](https://git-scm.com)

- [CMake 3.24 or above](https://cmake.org/download/)

- [Vulkan 1.3](https://vulkan.lunarg.com)

- Windows only
  - Build With Visual Studio
    - [Visual Studio 2019/2022](https://visualstudio.microsoft.com/downloads/)
    - 👇 Install the following workloads:
    - Game Development with C++
    - MSVC v142 or above | x64/x86
    - C++ 2022 redistributable update

- Linux only
  - Build With GNU
    - GCC 9.x or above
    - Make

- MacOS only
  - Build With Xcode
    - [Xcode](https://developer.apple.com/xcode/)
  
## Setup Repository

---

```shell
git clone https://github.com/Cesio137/Nanometro.git
```

## Building the Engine

---

#### Setup Enviroment Variables

* Setup Vulkan  
  * Create a variable called `VK_SDK_PATH` and `VULKAN_SDK` if do not exist:
    * ```Path
      <Path to Vulkan>/x.x.x/
      ```

#### Windows

* Setup Project.
  * Create a `build` folder and open terminal inside.
  * Commands to generate project
    * ```bash
      cmake .. --preset=VS2022_Debug
      make .. --preset=VS2022_Release
      ```
    * ```bash
      cmake .. --preset=VS2019_Debug
      cmake .. --preset=VS2019_Release
      ```

#### Linux

* Setup Project.
  
  * Create a `build` folder and open terminal inside.
  
  * Commands to generate project
    
    * ```bash
      cmake .. --preset=Unix_Debug
      cmake .. --preset=Unix_Release
      ```    

#### Mac OS

* Setup Project.
  
  * Create a `build` folder and open terminal inside.
  
  * to generate project using XCode
    
    * ```bash
      cmake .. --preset=XCode
      cmake .. --preset=Unix
      ```