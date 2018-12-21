# 简介
cuda的使用，一般是作为其他语言在GPU计算上的辅助工具。其文件需要使用nvcc作为编译工具，其生成 ` .o `文件作为下一步程序连接的源文件。nvcc与g++或mvsc的联合编译，需要手动将其编译文件路径，生成文件名，编译参数传递给nvcc。本文主要介绍，nvcc编译器的使用。
# nvcc编译器的使用结构
 
```
 cuda.input = CUDA_SOURCES
 cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
 cuda.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
 cuda.dependency_type = TYPE_C
 QMAKE_EXTRA_COMPILERS += cuda
```
## input
待编译文件名称
## output
输出文件名，与地址，本文中使用qmake作为工具，所以使用QMAKE_FILE_BASE作为路径导向。
## commands
编译条件
### 格式
cuda.coumands = 编译器地址 编译命令 编译条件 cuda头文件地址 cuda库  -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
### 编译器地址
* widows：nvcc.exe文件地址
* linux： /user/local/cuda/..nvcc 地址

### 编译命令 
-c

### 编译条件
nvidia官方文档网址  https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html
--compiler-options options,... 语句可以使用文档中不包含涵的条件语句 例如：-page，-fPIC等。其语法为：```--compiler-options -fPIC， ```或 ```-Xcompiler -fPIC,``` 。此语句只可使用多次，但是单次后所加条件仅为一条。
### cuda头文件地址和库
* Windows ：安装时cuda自动配置环境变量 `CUDA_PATH`以共使用
* Linux ：`cuda-9.0` 或其他版本安装目录下的链接 `cuda` 文件
* cuda库中主要使用 ``` -lcuda -lcudart ```


