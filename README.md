# VRParser
## 目的
本仓库是应用于康复工程实验室VR程序保存的二进制数据的解析和转码。
## 结构
### `parser`
此文件夹下存放库的核心功能。

`vrEegToBrainVision`：转码二进制函数，源文件为eeg.bin，目的文件为BrainAnalyser使用的.eeg文件。

`vrMarkerToBrainVision`：转码所有的marker标记，源文件为marker.txt，目的文件为BrainAnalyser的.vmkr文件。只提取eeg的marker，所有marker有唯一命名。

`vrEegWriteBrainVisionHeader`：拷贝eeg的头文件，单纯的文本拷贝，因为对于所有的数据的头文件都统一。

`vrEegConvertAllInFolder`：转码源文件夹的eeg相关数据，内容是依次调用上文的三个功能，修改eeg和marker文件的名称需要同步修改header的名称。

### `test`
此文件夹下存放测试`parser`的代码。可选择编译。

## 依赖
`CMake (minimum 3.12.0)`

`Visual Studio 2019`

## 编译

1. 克隆本仓库到本地
   ```
   git clone git@github.com:rehabsdu/VRParser.git`
   ```
2. 导航到根目录，执行cmake
    ```
    mkdir build && cd build
    cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug ..
    ```
3. 打开.sln工程编译出DLL文件。
   
## 待施工
1. Wrappers
2. Emg Parser
3. FT Parser

## 其他
* 作者：郝再军
* 邮箱：zaijun521@gmail.com