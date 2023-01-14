# Lumen

## Suported Platforms

---



- [x] Windows

- [ ] Linux(Help Wanted)

- [ ] Mac(Help Wanted)

## Download and Install

---



- [Git](https://git-scm.com)

- [CMake 3.23 or above](https://cmake.org/download/)

- [Visual Studio 2019/2022](https://visualstudio.microsoft.com/downloads/) `Windows only`

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
    * ```Path to Qt/6.2.4/msvc2019_64/bin
      <Path to Qt>/6.2.4/<your build tool>/bin
      ```
    * ```
      <Path to Qt>/6.2.4/<your build tool>/lib
      ```
* Run the `GenerateProject.bat` to create the soluction.
* Go to `build` folder and open the VS soluction.
* to generate project using command line just create a `build` folder and open terminal inside then type `cmake .. -G -DBUILD_SHARED_LIBS:BOOL="0" -DUSE_DOUBLE_PRECISION:BOOL="1" -DINSTALL_CMAKE_FILES:BOOL="0" -DGLFW_VULKAN_STATIC:BOOL="1" -DGLFW_USE_HYBRID_HPG:BOOL="1" -DBUILD_PYBULLET:BOOL="0" "Visual Studio XX XXXX"`

#### Linux | MAC
* Setup QT  
  * Add to enviroment variables:
    * ```
      <Path to Qt>/6.2.4>/<your build tool>/bin
      ```
    * ```
      <Path to Qt>/6.2.4/<your build tool>/lib
      ```.
* To generate project using command line just create a `build` folder and open terminal inside then type `cmake .. -DBUILD_SHARED_LIBS:BOOL="0" -DUSE_DOUBLE_PRECISION:BOOL="1" -DINSTALL_CMAKE_FILES:BOOL="0" -DGLFW_VULKAN_STATIC:BOOL="1" -DGLFW_USE_HYBRID_HPG:BOOL="1" -DBUILD_PYBULLET:BOOL="0"`