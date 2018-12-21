#简介
本文用于qt程序的打包，因windows打包简单，在此不进行介绍。

# linux 打包

## 打包方法一

### 方法
* 找到需打包的文件，如：` exe ` 
* 执行 ` ldd exe ` 若是存在未能发现的 ` .so ` 文件。则将其加入到环境中，方法如下：

```
# 找到未能找到的库文件 debug 文件中 存在 将其加入到统一的文件夹下：如 lib 
# 打开lib文件夹 执行pwd，copy其路径
sudo gedit(vim) /etc/ld.so.conf
# 将拷贝的路径加入其中
```

* 在其同级目录下增加一个文件夹，名字自取，如 ` copy `
* 制作 `copy.sh` 脚本文件，格式如下：

```
#! /bin/bash
 
# 执行脚本时在终端输入　./copy.sh ./test ./copy
# 其中./test为ldd所要查看的可执行程序的路径，./copy为依赖文件最终拷贝到的文件夹路径
 
# 以下三个参数为终端输入
# $0 为 ./copy.sh
# $1 为 ./test
# $2 为 ./copy
 
 
# awk 后　$0,$1,$2为终端日志的字符串，以空格为分隔符，只在awk本行起作用
# 将字符串重定向到dependList
dependList=$( ldd $1 | awk '{if (match($3,"/")){ print $3}}' )
 
 
# 输出　./test
# echo $1
 
# 拷贝依赖
cp $dependList $2
# 拷贝可执行程序
cp $1 $2

```
* 执行 ``` ./copy.sh exe ./copy ```

### 说明

当目标机器上无程序需要的相关环境时使用此方法打包。缺点是包过大，不易传输，且若是目标机器上存在相关环境，则照成库重复。虽然对程序运行没有影响，但是重复是不可原谅的。

## 打包方法二

### 方法
* 找到需打包的文件，如：` exe ` 将其放入到一个空的文件夹下
* 执行 ` ldd exe ` 若是存在未能发现的 ` .so ` 文件。则将其加入到环境中，方法如下：

```
# 找到未能找到的库文件 debug 文件中 存在 将其加入到统一的文件夹下：如 lib ，此文件需与exe文件同目录
# 打开lib文件夹 执行pwd，copy其路径
sudo gedit(vim) /etc/ld.so.conf
# 将拷贝的路径加入其中
```
* 创建 ` pack.sh ` 文件，脚本格式如下：

```
#!/bin/sh

exe="neurosem-imageserver" #发布的程序名称
des="/home/fbt/private/shaocong.wang/dabaofabu/neurosem-imageserver" #你的路径

deplist=$(ldd $exe | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')
cp $deplist $des
```
* 创建 ` exe.sh ` 文件，文件名必须与程序名相同。格式如下：

```
#!/bin/sh
appname=`basename $0 | sed s,\.sh$,,`
dirname=`dirname $0`
tmp="${dirname#?}"
if [ "${dirname%$tmp}" != "/" ]; then
dirname=$PWD/$dirname
fi
LD_LIBRARY_PATH=$dirname
export LD_LIBRARY_PATH
$dirname/$appname "$@"

```
此格式不必更改

* 创建说明文件，简单例子如下：


```
# install-description
# 简介
本文用于ne-imaged安装说明

# 环境配置
× cuda9.0
× opencv3.2及以上
× fbt027

# 环境搭建
1. 在本文件同级目录打开控制台程序
2. 执行 ` cd lib `
3. 执行 ` pwd `,复制输出的文件路径
4. 执行 `  sudo gedit /etc/ld.so.conf `或`  sudo vim  /etc/ld.so.conf `。
5. 在打开的文件内部贴上复制的路径

#运行

初次运行，应当先执行：

chmod -x neurosem-imaged
chmod -x neurosem-imaged.sh

执行：  ./neurosem-imaged.sh 

```

### 说明
此包远小于上包，不过需要配置环境。
