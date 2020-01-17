# WinDBG脚本

## 1 实验环境

1. VirtualBox 32位 Windows 7
2. Win 7可用的WinDBG

## 2 实验目的

1. 熟悉WinDBG的使用和一些常用命令。
2. 请修改 32 位 Windows 7 下的计算器的显示过程，使得当你输入的内容是特定数字如 "999" 的时候通过调试器脚本自动改为 "666"。

## 3 实验过程

### 3.1 WinDBG的安装

- 下载 Windows 7 可用的 WinDBG
  - WinDBG 早年是一个单独的工具，后来被包含到了 Windows SDK 中并且不再提供单独下载，根据官方文档你需要下载 Windows SDK 的 ISO 镜像并选择**仅安装 WinDBG**。
  - [Windows 7 SDK 在线安装程序](https://www.microsoft.com/en-us/download/details.aspx?id=8279)，在主机下载后，通过共享文件夹从主机共享到虚拟机，在虚拟机安装(一直下一步就行)，成功安装的截图如下。
    
    <img src="imgs/windbginstall.png" width=70%>

### 3.2 WinDBG的基本使用

- 打开可执行文件`File -> Open Executable`
- 

### 3.3 WinDBG脚本实验

### 3.4 修改计算器

## 4 实验总结 

1. 安装WinDBG的问题
   原因是使用了不同版本的Windows SDK(Soft Development Kit)，包含了开发该Windows版本所需的开发该windows版本所需的windows函数和常数定义、API函数说明文档、相关工具和示例。
   
   <img src="imgs/windbgerror.png" width=70% height=70%>

## 5 参考文档

- [小天使的代课教材](https://anjingcuc.github.io/courses-wiki/substitute/windbg-script/)
- [Windows SDK 和模拟器存档](https://developer.microsoft.com/zh-cn/windows/downloads/sdk-archive)
