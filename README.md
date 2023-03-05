# Lumen

## Suported Platforms

---

- [x] Windows

- [ ] Linux(Help Wanted)

- [ ] Mac(Help Wanted)

## Download and Install

---

- [Git](https://git-scm.com)

- [CMake 3.22 or above](https://cmake.org/download/)

- [Visual Studio 2019/2022](https://visualstudio.microsoft.com/downloads/) `Windows only`
  
  * Install the following workloads:
    - Game Development with C++
    - MSVC v142 or above | x64/x86
    - LLVM Clang(Optional)
    - C++ 2019 redistributable update

- [QT 6.2.4 LTS](https://www.qt.io/download)

- [Vulkan 1.3](https://vulkan.lunarg.com)

## Setup Repository

---

```shell
git clone https://github.com/Cesio137/Lumen.git
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
* Setup Project.
  * Create a `build` folder and open terminal inside.
  * to generate project using Visual studio 2022
    * ```bash
      cmake .. --preset=VS2022
      ```
  * to generate project using Visual studio 2022 and LLVM Clang
    * ```bash
      cmake .. --preset=VS2022_Clang
      ```
  * to generate project using Visual studio 2019
    * ```bash
      cmake .. --preset=VS2019_Clang
      ```
  * to generate project using Visual studio 2019 and LLVM Clang
    * ```bash
      cmake .. --preset=VS2019_Clang
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