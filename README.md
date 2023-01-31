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
* to generate project using command line just create a `build` folder and open terminal inside then type `cmake .. -G -DINSTALL_CMAKE_FILES:BOOL="0" -DGLFW_INSTALL:BOOL="0" -DBGFX_LIBRARY_TYPE:STRING="STATIC" -DBUILD_EXAMPLES:BOOL="0" -DGLFW_BUILD_TESTS:BOOL="0" -DGLFW_USE_HYBRID_HPG:BOOL="1" -DBUILD_UNIT_TESTS:BOOL="0" -DOPENCL_LIB_DIR:PATH="/lib" -DUSE_DOUBLE_PRECISION:BOOL="1" -DBUILD_CPU_DEMOS:BOOL="0" -DGLFW_BUILD_DOCS:BOOL="0" -DOPENCL_INCLUDE_DIR:PATH="/include" -DBUILD_OPENGL3_DEMOS:BOOL="0" -DBUILD_BULLET2_DEMOS:BOOL="0" -DGLFW_BUILD_EXAMPLES:BOOL="0" -DCMAKE_STATIC_LINKER_FLAGS_RELEASE:STRING="" -DBUILD_DOCS:BOOL="0" -DGLFW_VULKAN_STATIC:BOOL="1" -DBUILD_TESTING:BOOL="0" "Visual Studio XX XXXX"`

#### Linux | MAC
* Setup QT  
  * Add to enviroment variables:
    * ```
      <Path to Qt>/6.2.4>/<your build tool>/bin
      ```
    * ```
      <Path to Qt>/6.2.4/<your build tool>/lib
      ```.
* To generate project using command line just create a `build` folder and open terminal inside then type `cmake .. -DINSTALL_CMAKE_FILES:BOOL="0" -DGLFW_INSTALL:BOOL="0" -DBGFX_LIBRARY_TYPE:STRING="STATIC" -DBUILD_EXAMPLES:BOOL="0" -DGLFW_BUILD_TESTS:BOOL="0" -DGLFW_USE_HYBRID_HPG:BOOL="1" -DBUILD_UNIT_TESTS:BOOL="0" -DOPENCL_LIB_DIR:PATH="/lib" -DUSE_DOUBLE_PRECISION:BOOL="1" -DBUILD_CPU_DEMOS:BOOL="0" -DGLFW_BUILD_DOCS:BOOL="0" -DOPENCL_INCLUDE_DIR:PATH="/include" -DBUILD_OPENGL3_DEMOS:BOOL="0" -DBUILD_BULLET2_DEMOS:BOOL="0" -DGLFW_BUILD_EXAMPLES:BOOL="0" -DCMAKE_STATIC_LINKER_FLAGS_RELEASE:STRING="" -DBUILD_DOCS:BOOL="0" -DGLFW_VULKAN_STATIC:BOOL="1" -DBUILD_TESTING:BOOL="0"`