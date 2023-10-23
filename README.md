# Nanometro

## Suported Platforms

---

- [x] Windows

- [ ] Linux(Help Wanted)

- [ ] Mac(Help Wanted)

## Download and Install

---

- [Git](https://git-scm.com)

- [CMake 3.24 or above](https://cmake.org/download/)

- [Visual Studio 2019/2022](https://visualstudio.microsoft.com/downloads/) `Windows only`
  
  * Install the following workloads:
    - Game Development with C++
    - MSVC v142 or above | x64/x86
    - C++ 2022 redistributable update

- [QT 6.2.4 LTS](https://www.qt.io/download)

- [Ninja-Build (Optional)](https://github.com/ninja-build/ninja/releases)

- [Vulkan 1.3](https://vulkan.lunarg.com)

## Setup Repository

---

```shell
git clone https://github.com/Cesio137/Nanometro.git
```

## Building the Engine

---

#### Windows

* Setup QT  
  * Add to enviroment variables:
    * ```Path
      <Path to Qt>/6.2.4/<your build tool>/bin
      ```
    * ```
      <Path to Qt>/6.2.4/<your build tool>/lib
      ```
    * ```
      <Path to Ninja>(Optional)
      ```
* Setup Project.
  * Create a `build` folder and open terminal inside.
  * to generate project using Visual studio 2022 Debug(Recommended)
    * ```bash
      cmake .. --preset=VS2022_Debug
      ```
  * to generate project using Visual studio 2022 Release(Recommended)
    * ```bash
      cmake .. --preset=VS2022_Release
      ```
  * to generate project using Visual studio 2019 Debug
    * ```bash
      cmake .. --preset=VS2019_Debug
      ```
  * to generate project using Visual studio 2019 Release
    * ```bash
      cmake .. --preset=VS2019_Release
      ```
  * to generate project using Ninja and Visual studio 20XX
    * ```bash
      cmake .. --preset=Ninja_VS20XX_<Debug or Release>
      ```

#### Linux

* Setup QT  
  
  * Add to enviroment variables:
    * ```
      <Path to Qt>/6.2.4>/<your build tool>/bin
      ```
    * ```
      <Path to Qt>/6.2.4/<your build tool>/lib
      ```

* Setup Project.
  
  * Create a `build` folder and open terminal inside.
  
  * to generate project using Unix Makefile
    
    * ```bash
      cmake .. --preset=Unix
      ```
  
  * to generate project using Unix Makefile and LLVM Clang
    
    * ```bash
      cmake .. --preset=Unix_clang
      ```

#### Mac OS

* Setup QT  
  
  * Add to enviroment variables:
    
    * ```
      <Path to Qt>/6.2.4>/<your build tool>/bin
      ```
    * ```
      <Path to Qt>/6.2.4/<your build tool>/lib
      ```

* Setup Project.
  
  * Create a `build` folder and open terminal inside.
  
  * to generate project using XCode
    
    * ```bash
      cmake .. --preset=XCode
      ```
  
  * to generate project using Unix Makefile
    
    * ```bash
      cmake .. --preset=Unix
      ```
  
  * to generate project using Unix Makefile and LLVM Clang
    
    * ```bash
      cmake .. --preset=Unix_clang