---
layout: post
title: "shell 用法总结"
date: 2015-07-26 12:44:39 +0800
comments: true
categories: shell
---

* list element with functor item
{:toc}

## 控制语句

### if

``` sh 
if list; then list; [elif list ; then list; ] ... [ else list; ] fi
```
if 后面的list执行，如果返回值为0，则执行then后面的list，否则会执行elif后面的list，直到有一个list的执行结果为0，则执行对应的then后面的list，如果所有elif的执行结果都是非0，则会执行else的后面的list。

这里需要说明一下if后面并不是只能接条件语句，可以接任何的命令，最终是判断这一串语句的返回值是不是0

<!-- more -->

### for 

for 有两种格式
``` sh
for name [ [ in [ word ... ] ] ; ] do list ; done
```
name的值会遍历word列表，并执行list

用法举例1：
``` sh
for i in {1..3}
do
    echo $i
done
```
output: 

    1
    2
    3

说明{1..3}会生成"1 2 3"的一个列表

用法举例2：
``` sh
for host in 70 72 110
do
    ssh 192.168.10.$host "grep 'xxx' /data/logs/xxxx"
done
```
分别从三台机器上查看日志

``` sh
for (( expr1 ; expr2 ; expr3 )) ; do list ; done
```
语法和c语言的一样只是是两个括号
``` sh
for (( i = 1; i < 10; i += 2 ))
do
    echo $i
done
```
output:

    1
    3
    5
    7
    9

### while 

``` sh
while list; do list; done
until list; do list; done
```
while 只要 while后面的list执行返回值为0，则会执行do后面的list, until与while相反

用法举例：
``` sh
while read line
do
    echo $line
done
```
从标准输入依次读取一行直到标准输入结束

### case

``` sh
case word in [ [(] pattern [ | pattern ] ... ) list ;; ] ... esac
```
word匹配到对应的正则会执行对应的list语句

举例：
``` sh
case $1 in 
    start | begin )
        echo "start"
        ;;
    stop | end )
        echo "stop"
        ;;
    *)
        echo "default"
        ;;
esac
```
处理脚本的参数

### select 

``` sh
select name [ in word ] ; do list ; done
```
多用于用户交互，给一个列表参数供选择，select是循环选择，需要在list里面写break退出循环，多与case配合使用

``` sh
select word in start stop exit
do
    case $word in
        exit)
            exit 0
            ;;
        *)
            echo $word
            ;;
    esac
done
```
执行过程：

![shell-select]( /downloads/image/shell-select.png)

