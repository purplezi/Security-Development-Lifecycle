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

- 调试时所需：**源代码**和**符号文件(pdb文件)**
- 32位 win7 离线符号表
- 打开可执行文件`File -> Open Executable`(出现int3后，表示已经打开完成)，在`file->Symbol search path`选择符号文件所在的文件夹(不要直接选择符号文件)
  - 在vs2019下编写`hello world`的.c文件，生成exe后放入win7 虚拟机
  - 将同目录下的pdb也放入win7虚拟机
    
- 选择`attach to a Process`，即可看到本机所有的进程信息，选择要调试的进程。
- 安装windows符号文件`.pdb`文件 使用Windows符号表服务器
- 指令集
  |指令|作用|
  |---|---|
  |.symfix|指定本地缓存目录|
  |.sympath|设置符号路径，包括本地缓存和远程符号服务器|
  |.reload|重新加载模板|
  |x|查看模块符号|
  |bu|下断点|
  |bl|列出断点|
  |g|继续执行程序|
  |k|查看调用堆栈|
  |lm|列出当前进程加载的模块|

### 3.3 WinDBG脚本实验

#### 3.3.1 修改记事本

- 在win7 虚拟机的桌面新建`command.txt`，内容如下：
    ```
    as /mu content poi(esp+0n24)
    .block{.if($scmp("${content}","123456")==0){ezu poi(esp+0n24) "hacked";}.else{.echo content}}
    g

    # 以下为相关解释
    esp+0n24：记事本写入信息的起始位置
    poi用于获取地址中的内容
    as 用于起别名
    /ma 将别名的等价值设置为从地址Address开始的null结尾的ASCII字符串
    /mu 将别名的等价值设置为从地址Address开始的null结尾的Unicode字符串
    ea 地址 "abc" 表示在0x445634地址写入Ascii字符串abc 不包含结束符0
    eza 地址 "abc" 表示在0x445634地址写入Ascii字符串abc 包含结束符0
    eu 地址 "abc" 表示在0x445634地址写入Unicode字符串abc 不包含结束符0
    ezu 地址 "abc" 表示在0x445634地址写入Unicode字符串abc 包含结束符0
    ```


#### 3.3.2 修改计算器

- 计算偏移地址
- 在win7 虚拟机的桌面新建`command.txt`，内容如下：
    ```
    as /mu content poi(esp+8)
    .block{.if($scmp("${content}","999")==0){ezu poi(esp+8) "666";}.else{.echo content}}
    g
    ```

## 4 实验总结 

1. 安装WinDBG的问题
   原因是使用了不同版本的Windows SDK(Soft Development Kit)，包含了开发该Windows版本所需的开发该windows版本所需的windows函数和常数定义、API函数说明文档、相关工具和示例。
   
   <img src="imgs/windbgerror.png" width=70%>

2. `.reload`的时候出错
   
   <img src="imgs/symbolerror.png" width=70%>

   - 原因：没有载入符号表？

## 5 参考文档

- [小天使的代课教材](https://anjingcuc.github.io/courses-wiki/substitute/windbg-script/)
- [Windows SDK 和模拟器存档](https://developer.microsoft.com/zh-cn/windows/downloads/sdk-archive)
