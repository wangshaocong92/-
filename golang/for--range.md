# 简介

本文件用于`for k,y := range rag{}`用法的介绍，和常见的坑

# 用法

golang基于少即是多的设计原则，在数据迭代的应用场景仅提供了for循环作为工具。C系相关的`while` `do..while`
等方式没有提供。
```
for...range {
}
```
是for的变种，其可以同时返回`键`值和`值`值,相较于普通的C系语言方便使用，使用案例：
```
for key, value := range myMap {
		fmt.Printf("map[%x]=%x\n", key, *value)
	}

```
for...range的使用逻辑：

* range后方的迭代体，是其定义体的copy。而非其引用
* key和value是固定的变量，随着迭代的继续，将迭代体的值copy到key和value的内存中

# 坑

## 赋值而非取出

```
package main
 
import "fmt"
 
func main() {
	slice := []int{0, 1, 2, 3}
	myMap := make(map[int]*int)
 
	for index, value := range slice {
		myMap[index] = &value
	}
	fmt.Println("=====new map=====")
	prtMap(myMap)
}
 
func prtMap(myMap map[int]*int) {
	for key, value := range myMap {
		fmt.Printf("map[%v]=%v\n", key, *value)
	}
}
```

期望输出：
```
=====new map=====
map[0]=0
map[1]=1
map[2]=2
map[3]=3
```
实际输出：
```
=====new map=====
map[0]=3
map[1]=3
map[2]=3
map[3]=3
```
分析：
此代码中为`map`赋值的操作，将value的地址赋给`map`的value，此时的地址为`for...range`  的地址。而不是`slice`相对元素的地址

## 迭代体为copy，而非引用
```
package main
import "fmt"
func main() {
	a := [3]int{1, 2, 3}
	for k, v := range a {
		if k == 0 {
			a[0], a[1] = 100, 200
			fmt.Print(a)
		}
		a[k] = 100 + v
	}
	fmt.Print(a)
}
```
实际输出为：
{[100][200][3]}{[101][102][103]}
期望输出：
{[100][200][3]}{[200][300][103]}

```
package main
import "fmt"
func main() {
	a := []int{1, 2, 3}
	for k, v := range a {
		if k == 0 {
			a[0], a[1] = 100, 200
			fmt.Print(a)
		}
		a[k] = 100 + v
	}
	fmt.Print(a)
}
```
实际输出为：
{[100][200][3]}{[101][200][103]}
期望输出：
{[100][200][3]}{[200][300][103]}
分析：
代码a，`range a` 是copy自`a array`。所以当对`range a`迭代时，虽然 `a array`发生了变化，可是`range a` 因为是copy体，没有随之变化。所以产生了实际结果
代码b，`range a` 是copy自`a slice`。slice为引用类型，其copy的是其地址即引用传递。当`a slice`改变时，其copy体`range a` 发生了同步变化。其第一个元素因为其使用逻辑的第二个逻辑，value 并不是a[0],所以
a[0]的变化未能影响到value的值，所以其实际输出的第一个值为`100+v`,即`101`

# 引用
[https://blog.csdn.net/anakinsun/article/details/89487669](https://blog.csdn.net/anakinsun/article/details/89487669)
[https://blog.csdn.net/idwtwt/article/details/87378419](https://blog.csdn.net/idwtwt/article/details/87378419)