# 简介
本文用于golang 的select关键字的使用说明

# select

A "select" statement chooses which of a set of possible send or receive operations will proceed. It looks similar to a "switch" statement but with the cases all referring to communication operations.
一个select语句用来选择哪个case中的发送或接收操作可以被立即执行。它类似于switch语句，但是它的case涉及到channel有关的I/O操作。
通俗来说，select就是用来监听和channel有关的IO操作，当 IO 操作发生时，触发相应的动作

# select作业逻辑

* For all the cases in the statement, the channel operands of receive operations and the channel and right-hand-side expressions of send statements are evaluated exactly once, in source order, upon entering the "select" statement. The result is a set of channels to receive from or send to, and the corresponding values to send. Any side effects in that evaluation will occur irrespective of which (if any) communication operation is selected to proceed. Expressions on the left-hand side of a RecvStmt with a short variable declaration or assignment are not yet evaluated.
* If one or more of the communications can proceed, a single one that can proceed is chosen via a uniform pseudo-random selection. Otherwise, if there is a default case, that case is chosen. If there is no default case, the "select" statement blocks until at least one of the communications can proceed.
简单来说，select语句使用时，检视每一个channal，若是其当前操作不在阻塞状态。其case后语句便有了可以被执行的资格。其原则如下：
* 当前select中，有一个channal准备就绪执行当前channal控制语句。若多个channal准备就绪，则随机执行一个channal的控制语句
* 当前无channal准备就绪，若存在default语句则执行default语句，否则阻塞等待。

# select的优先级设置

在select中利用default可以设置各个channal控制语句的执行优先级。使得不确定的随机执行确定化

```
a := make(chan int,1)
b := make(chan int,1)

for {
    select {
    case <-a:
        handleHigh(data)
    default:
        select {
        case <-b:
            handleLow(data)
        default:
           //空操作
        }
    }
}

```
