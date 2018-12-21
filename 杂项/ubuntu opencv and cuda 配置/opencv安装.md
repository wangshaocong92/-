# 简介
本文件包含于linux开发环境的配置。opencv的安装
# 前置
## cmake安装

```
sudo apt-get install cmake
```

# 安装
## 源码取得
opencv4.0  https://github.com/opencv/opencv/releases
opencv_contrib4.0 https://github.com/opencv/opencv_contrib/releases
## 文件配置
下载OpenCV3的源码```opencv```和```opencv_contrib```
新建文件将下载到的源码放入新建文件内。同时在文件内添加 `build` 文件，目录树如下：
```
- build \
- opencv \
- opencv_contrib \
```
注意：此处下载包若与本文中名称不同，则将文件名改为本文中的文件名
## cmake

进入 `build` 目录下 ，以下命令均在 `build` 目录下执行：
```
sudo apt-get install libgtk2.0-dev
sudo apt-get install pkg-config
cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules -DCMAKE_INSTALL_PREFIX=/usr/local -DWITH_CUDA=ON -DWITH_CUBLAS=ON -DBUILD_TIFF=ON OFF -DWITH_TBB=OFF -DWITH_IPP=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug ../opencv -G "Unix Makefiles"
```

## 执行编译和安装
上命令同文件执行：
```
make -j8
sudo make install
```