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

- [QT 6.5.x LTS](https://www.qt.io/download)

- [Vulkan 1.3](https://vulkan.lunarg.com)

- Windows only
  - Build With Visual Studio
    - [Visual Studio 2019/2022](https://visualstudio.microsoft.com/downloads/)
    - 👇 Install the following workloads:
    - Game Development with C++
    - MSVC v142 or above | x64/x86
    - C++ 2022 redistributable update
    - LLVM(Optional)

- Linux only
  - Build With GNU
    - GCC 9.x or above
    - Make
    - [LLVM(Optional)](https://github.com/llvm/llvm-project/releases)

- MacOS only
  - Build With Xcode
    - [Xcode](https://developer.apple.com/xcode/)
    - [LLVM(Optional)](https://github.com/llvm/llvm-project/releases)
  
## Setup Repository

---

```shell
git clone https://github.com/Cesio137/Nanometro.git
```

## Building the Engine

---

#### Setup Enviroment Variables

* Setup QT  
  * Create a variable called `QT_PATH`:
    * ```Path
      <Path to Qt>/6.5.x/
      ```

* Setup LLVM
  * Add to enviroment variables:
    * ```Path
      <Path to LLVM>/bin
      ```

#### Windows

* Setup Project.
  * Create a `build` folder and open terminal inside.
  * Commands to generate project
    * ```bash
      cmake .. --preset=VS2022_Debug
      ```
    * ```bash
      cmake .. --preset=VS2022_Release
      ```
    * ```bash
      cmake .. --preset=VSClang2022_Debug
      ```
    * ```bash
      cmake .. --preset=VSClang2022_Release
      ```
    * ```bash
      cmake .. --preset=VS2019_Debug
      ```
    * ```bash
      cmake .. --preset=VS2019_Release
      ```
    * ```bash
      cmake .. --preset=VSClang2019_Debug
      ```
    * ```bash
      cmake .. --preset=VSClang2019_Release
      ```

#### Linux

* Setup Project.
  
  * Create a `build` folder and open terminal inside.
  
  * Commands to generate project
    
    * ```bash
      cmake .. --preset=Unix
      cmake .. --preset=Unix_clang
      ```    

#### Mac OS

* Setup Project.
  
  * Create a `build` folder and open terminal inside.
  
  * to generate project using XCode
    
    * ```bash
      cmake .. --preset=XCode
      cmake .. --preset=Unix
      cmake .. --preset=Unix_clang
      ```