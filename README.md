# Lumen

## Download and Install

---

- [Git](https://git-scm.com)

- [CMake 3.23 or above](https://cmake.org/download/)

- [Visual Studio 2019/2022](https://visualstudio.microsoft.com/downloads/) `Windows only`

- [QT 6.2.4 LTS](https://www.qt.io/download)

- [Vulkan 1.3](https://vulkan.lunarg.com)



## Suported Platforms

---



- [x] Windows

- [ ] Linux(Help Wanted)

- [ ] Mac(Help Wanted)



## Setup Repository

---



```shell
git clone https://github.com/Cesio137/Lumen.git
```

```shell
git submodules init
```

```shell
git submodules update
```



## Building the Engine

---

#### Windows

* Setup QT  
  * Add to enviroment variables:
    * ```Path to Qt/6.2.4/msvc2019_64/bin
      Path to Qt/6.2.4/msvc2019_64/bin
      ```
    * ```
      Path to Qt/6.2.4/msvc2019_64/lib
      ```
* Run the `VS2019.bat` or `VS2022.bat` to create the soluction.
* go to `build` folder and open the VS soluction.