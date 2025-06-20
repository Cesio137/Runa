# Runa

Runa is a set of tools planned to be an open-source, real-time, cross-platform 2D and 3D engine.

## Suported Platforms

---

- [x] Windows

- [x] Linux(Help Wanted)

- [ ] Mac(Help Wanted)

## Download and Install

---

- [Git](https://git-scm.com)

- [CMake 3.15 or above](https://cmake.org/download/)

- [Xmake](https://vcpkg.io/en/)

- Windows only
  - Build With Visual Studio 2022
    - [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/)
    - 👇 Install the following workloads:
    - Game Development with C++
    - MSVC v142 or above | x64/x86
    - C++ 2015/2022 redistributable update

- Linux only
  - Build With GNU ```install with package manager```
    - GCC 9.x or above
    - make 
    - m4 
    - autoconf 
    - automake 
    - libtool
    - Perl
  
  - Python packages
    - Jinja2 ``` pip install Jinja2 ```
  
## Setup Repository

---

```shell
git clone https://github.com/Cesio137/Runa.git
```

## Building the Engine

---

#### Setup Project
Configure and install all dependencies
```shell
xmake
```

#### Generate cmake/vs files

* CMake
  * Commands to generate cmake project
    * ```bash
      xmake project -k cmake
      ``` 
* Visual Studio
  * Commands to generate visual studio project
    * ```bash
      xmake project -k vsxmake
      ```