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
xmake f --mode=debug
```
```shell
xmake f --mode=release
```

#### Generate cmake/vs files

* CMake
  * Commands to generate cmake project
    * ```shell
      xmake project -k cmake
      ``` 
* Visual Studio
  * Commands to generate visual studio project
    * ```shell
      xmake project -k vsxmake
      ```

### Thirdparty libraries

* Graphics
  * [SDL 3](https://github.com/libsdl-org/SDL/releases)
  * [Vulkan](https://github.com/KhronosGroup/Vulkan-Headers)
  * [Glad](https://github.com/Dav1dde/glad)
  * [GLM](https://github.com/g-truc/glm)
* UI
  * [ImGui](https://github.com/ocornut/imgui)
* IO
  * [ASIO non-boost](https://think-async.com/Asio/AsioAndBoostAsio)
  * [stb](https://github.com/nothings/stb)
* STL for C
  * [stc](https://github.com/stclib/STC)
* Script language
  * [luau](https://luau.org/)
* Json serd
  * [simdjson](https://github.com/simdjson/simdjson)