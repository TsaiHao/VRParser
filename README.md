# VRParser
## 目的
本仓库是应用于康复工程实验室VR程序保存的二进制数据的解析和转码。
## 结构
### `parser`
此文件夹下存放库的核心功能。
#### `include`
此文件夹包含`dllmain.h`头文件，`parser`库所有对外暴露函数签名都声明于此。在matlab中直接引用libparser需要输入此头文件。
#### `source`
此文件夹包含两部分，一部分`utils`文件夹包含库的一些辅助功能的纯C++实现。另外一部分是`dllmain`的代码的实现。
#### `wrapper`
此文件夹主要包含库的对其他语言的接口的包装，以及一些实例代码。

`matlab`文件夹包含用于matlab的接口，文件夹中的文件主要是纯matlab实现的功能，在`functions`中包含Matlab Mex封装的类接口，其功能都在文件名中有体现，编译这些代码的方式如下，以`GetMarkers.cpp`为例：

打开Matlab，导航至matlab下，在命令行键入：
```shell
mex functions/GetMarkers.cpp -I../../source -lparser
markers = GetMarkers('marker.txt');
```

### `test`
此文件夹下存放测试`parser`的代码。可选择编译。

## 依赖
`CMake (minimum 3.16.0)`

`Visual Studio 2019`
or
`Clion 2020`

## 编译

1. 克隆本仓库到本地
   ```
   git clone git@github.com:rehabsdu/VRParser.git`
   ```
2. 导航到根目录，执行cmake(Windows环境)
    ```shell
    mkdir build && cd build
    cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug ..
    ```
   需要生成matlab functions时需要指定：
   ```shell
   cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug -DADD_MATLAB=ON ..
   ```
   注意上面的命令需要系统安装matlab，并且添加到了PATH中。
3. 打开.sln工程编译出DLL文件。

## 其他
* 作者：郝再军(2018)
* 邮箱：zaijun521@gmail.com