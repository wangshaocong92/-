# 简介
本文件用于介绍opencv使用相关cuda库的安装
# 背景
## 版本
使用英伟达 `cuda 9.0` 版本作为ubuntu服务器 `opencv 4.0` 的辅助工具。

## 安装包地址
https://developer.nvidia.com/cuda-90-download-archive?target_os=Linux&target_arch=x86_64&target_distro=Ubuntu&target_version=1604&target_type=deblocal
其中有多种安装包可供选择，本次安装选择 `deb(local)` 作为安装资源

#前置工作
## 无限登陆现象解决
有两种可能造成无限登陆现象的产生，因已经解决此问题，两种可能未知是哪一种在此都将介绍
1.解决opencl冲突
* `alt+ctrl+F1` 进入tty模式。
* 运行 `sudo service ligntdm stop` 命令
* `sudo apt-get remove --purge nvidia-*` 删除英伟达相关软件
* `sudo apt-get autoremove`
* `sudo ./NVIDIA-linux-**.run --uninstall`
* 重新安装 
 `sudo ./NVIDIA-linux-**.run --no-opengl-files`
安装时依次选项如下：
  
```
1. accept
2. continueinstallation
3. Would you like to run the nvidia-xconfig ......
 NO
4. Install 32-Bit compatibility libraries? 
 NO
```
2.拉黑nouveau
* 测试是否有nouveau插件
 执行
 `lsmod |grep nouveau`
如果有输出，则需要拉黑他。否则可以继续安装
* 拉黑
 `vim /etc/modprobe.d/blacklist.conf`
在打开文件的最后一行加上
 `blacklist nouveau`
 保存关闭
执行：
```
  sudo update-initramfs -u
  sudo reboot
```
重启后执行
  `lsmod |grep nouveau`
无输出则完成

# 安装步骤
### 1.创建文件夹用来，存储下载的 `.deb` 文件
此处安装的文件为 ``` cuda-repo-ubuntu1604-9-0-local_9.0.176-1_amd64.deb ```
### 2.依次输入以下命令行
```
`sudo dpkg -i cuda-repo-ubuntu1604-9-0-local_9.0.176-1_amd64.deb`
`sudo apt-key add /var/cuda-repo-<version>/7fa2af80.pub`
`sudo apt-get update`
`sudo apt-get install cuda`

```
### 3.配置环境变量输入以下命令
```
sudo gedit  /etc/profile
```
在文件结尾处依次键入如下命令
```
export  PATH=/usr/local/cuda-9.0/bin:$PATH
export  LD_LIBRARY_PATH=/usr/local/cuda-9.0/lib64:$LD_LIBRARY_PATH
```
重启
```
sudo reboot　
```




