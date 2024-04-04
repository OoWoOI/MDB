# 微型数据库系统

## 初版_v1

### 程序设计:界面切换流程

（1）操作界面的关系

```c
/*************************************************************************
	> File Name: 01.user_interface.c
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Apr 2024 05:20:41 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int page1_usage() {
    printf("1 : goto page2\n");
    printf("2 : goto page3\n");
    printf("3 : goto page4\n");
    int x = -1;
    do {
        printf("input : ");
        scanf("%d", &x);
    } while (x < 1 || x > 3);
    return x;
}

int page2_usage() {
    printf("0 : back to page1\n");
    printf("1 : goto page5\n");
    int x = -1;
    do {
        printf("input : ");
        scanf("%d", &x);
    } while (x < 0 || x > 1);

    return x;
}

int page4_usage() {
    printf("0 : back to page1\n");
    printf("1 : goto page5\n");
    int x = -1;
    do {
        printf("input : ");
        scanf("%d", &x);
    } while (x < 0 || x > 1);

    return x;
}

void page3_run() {
    int arr[10], len = 0;
    for (int i = 0; i < 10; i++) arr[i] = rand() % 100;
    for (int i = 0; i < 10; i++) {
        len += printf("%3d", i);
    }
    printf("\n");
    for (int i = 0; i < len; i++) printf("-");
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%3d", arr[i]);
    }
    printf("\n\n");
    return ;
}

void page5_usage() {
    printf("hello this is page5\n");
    return ;
}


int main() {
    srand(time(0));
    int status = 1;

    while (1) {
        switch (status) {
            case 1: {
                printf("into page1 :\n");
                int x = page1_usage(); 
                if (x == 1) status = 2;
                else if (x == 2) status = 3;
                else if (x == 3) status = 4;
            } break;
            case 2: {
                printf("into page2 :\n");
                int x = page2_usage();
                if (x == 0) status = 1;
                else if (x == 1) status = 5;
            } break;
            case 3: {
                
                printf("into page3 :\n");
                page3_run();
                status = 5;
            } break;
            case 4: {
                printf("into page4 :\n");
                
                int x = page4_usage();
                
                if (x == 0) status = 1;
                else if (x == 1) status = 5;
                
            } break;
            case 5: {
                printf("into page5 :\n"); 
                page5_usage();
                status = 1;
            } break;
        }
    }
    
    return 0;
}

```



### 项目设计:操作层与数据层

（1）项目设计的思路

> 认识到代码只是对于工程师的思想表达，只要设计合理不用担心无法代码实现。

（2）分离操作层与数据层

> 操作层：交互界面、
>
> 数据层：学生表、表1、表2

### 项目实现:用户交互流程

#### 用户交互流程



#### 多表注册功能

（1）什么是注册功能

> `__attribute__`关键字
>
> 可以修改函数的属性，`__attribute__((constructor)) void test();` 使其先于主函数执行
>
> 什么是注册函数：将某个功能注册到系统中的函数

```c
/*************************************************************************
	> File Name: 02.attribute.c
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Apr 2024 07:50:22 PM CST
 ************************************************************************/

#include<stdio.h>

int num[10];

__attribute__((constructor))void test1() {
    num[0] = 1;
    return ;
} 
__attribute__((constructor))void test2() {
    num[1] = 10086;
    return ;
} 
__attribute__((constructor))void test3() {
    num[2] = 10087;
    return ;
} 

int main() {
    for (int i = 0; i < 10; i++) {
        printf(" %3d", num[i]);
    }
    printf("\n");
    
    return 0;
}

```

（2）项目设计：交互过程中的配置信息


> 问题1：表信息是如何存储的
>
> ​			答：表中存在着一个注册函数，系统启动，就会更新表信息。源代码的形式
>
> 问题2：表切换过程中，数据是怎么样展示出来的？	
>
> ​			答：每个表都应该对应着有一个数据打印函数，按照格式化输出

（3）项目实现：多表的注册功能

> 数据库表中，为什么需要将table_name定义为静态属性？
>
> staic修饰的变量或者函数，在编译链接过程中，只有当前对象文件才可见，避免了多文件编译过程中出现重名的冲突。同时局部变量经由static修饰后，生命周期就会变化；

#### static关键字

//简介

>  在C语言中，static关键字有多种作用，取决于它所修饰的上下文。static关键字在C语言中的作用是控制标识符（变量、函数、结构体、联合）的链接属性和作用域。

//主要作用

- 在函数内部声明的变量前加上static关键字，使该变量成为静态局部变量。

> 静态局部变量与普通局部变量的区别在于，静态局部变量的生存期贯穿整个程序的执行过程，而不是仅在函数调用时存在。静态局部变量的值在函数调用之间保持不变。

```c
void foo() {
    static int count = 0; // 静态局部变量
    count++;
    printf("Count: %d\n", count);
}
```

- 在全局变量中使用static：


> 在全局变量声明前加上static关键字，使该全局变量的作用域限制在当前源文件内，不会被其他源文件访问。
> 这种用法可以用于实现信息隐藏和限制全局变量的作用范围。

```c
static int globalVar = 10; // 静态全局变量，只能在当前源文件内访问
```

- 在函数声明中使用static：


> 在函数声明前加上static关键字，将函数的链接属性限制为内部链接，使其只能在当前源文件内部调用。
> 这种用法可以用于限制函数的作用范围，以及避免与其他源文件中具有相同名称的函数发生冲突。

```c
static int add(int a, int b); // 内部链接的函数声明
```

- 在结构体和联合中使用static：


>  在结构体或联合声明前加上static关键字，使其成为静态结构体或静态联合。
>  静态结构体或联合的实例仅可在当前源文件内访问。

```c
static struct MyStruct {
    int x;
    int y;
};
```

#### extern关键字

//简介

> 在C语言中，`extern`关键字用于声明一个变量或函数的外部链接性，它告诉编译器该标识符在其他文件中定义。

//作用

（1）**声明外部变量**：

> 在一个文件中使用`extern`关键字来声明一个在其他文件中定义的全局变量。这样做可以让编译器知道该变量是在其他地方定义的，而不是在当前文件中定义。

```c
extern int globalVar; // 声明全局变量globalVar，该变量在其他文件中定义
```

（2）**声明外部函数**：

> 在一个文件中使用`extern`关键字来声明一个在其他文件中定义的函数。这样做可以让编译器知道该函数是在其他地方定义的，而不是在当前文件中定义。

```c
extern int add(int a, int b); // 声明函数add，该函数在其他文件中定义
```

（3）**在头文件中使用**：

> 在头文件中使用`extern`关键字来声明外部变量或函数，以便在多个源文件中使用相同的全局变量或函数。

```c
// header.h
#ifndef HEADER_H
#define HEADER_H

extern int globalVar; // 声明外部全局变量
extern int add(int a, int b); // 声明外部函数

#endif

```

（4）**防止重复定义**：

> - 在多个源文件中包含同一个头文件时，`extern`可以确保只有一个文件定义了这些变量或函数，避免重复定义的错误。

#### `attribute`关键字

//简介

> `__attribute__`是GCC（GNU Compiler Collection）编译器提供的一种特性，用于向编译器提供关于变量、函数和类型等方面的额外信息，以便进行优化、警告和其他操作。

//作用

1. **声明属性**：

   可以使用`__attribute__`关键字为变量、函数或类型添加属性。这些属性可以用于告诉编译器如何对待这些实体，例如告诉编译器如何对待内存对齐、函数调用约定等。

```c
int my_variable __attribute__((aligned(16))); // 声明变量my_variable，要求16字节对齐
void my_function() __attribute__((noreturn)); // 声明函数my_function，告诉编译器该函数不会返回
```

1. **启用警告**：

   可以使用`__attribute__`启用或禁用特定的警告。这对于编译器警告过多或不够准确时进行控制很有用。

```c
void my_function(int x) __attribute__((deprecated)); // 声明函数my_function，并启用弃用警告
```

1. **优化控制**：

   可以使用`__attribute__`来控制编译器的优化行为，例如告诉编译器哪些函数是纯函数（pure）或不会改变全局状态（const）。

```c
int square(int x) __attribute__((pure)); // 声明函数square是一个纯函数
```

1. **约束条件**：

   可以使用`__attribute__`来为函数参数或返回值添加约束条件，例如告诉编译器某个参数是指针并且不可为空。

```c
int *my_function(int x) __attribute__((nonnull)); // 声明函数my_function，并告诉编译器参数不可为空
```

1. **构造器和析构器**：

   可以使用`__attribute__`将函数标记为构造器或析构器，这些函数在程序启动或终止时会自动执行。

```c
void my_constructor() __attribute__((constructor)); // 声明my_constructor为构造器
void my_destructor() __attribute__((destructor)); // 声明my_destructor为析构器
```

#### 切换表信息

> 功能分析：
>
> 选择表后，进入到对应表的操作界面【TABLE_USAGE】，根据操作界面的提示信息完成对应表操作。

### 项目实现:数据的增删改查

#### 查询

（1）实现查询功能之前需要完成对文件的读写操作；

> 准备工作：准备data文件夹，准备一份student_data.dat数据，只准备一张表student_table;
>
> （1）子功能1：加载二进制数据，打开文件，依次读入每条数据，使用链表结构，存储数据；
>
> （2）子功能2：打印数据列表，依次打印每条数据，打印表头信息

（2）关闭数据表操作

> 在选择一张表之前，应该先关闭上一张表，因此在初始化下一张表之前，先清空table_data的数据，释放链表中的资源。随后关闭文件操作；

（3）打印数据表操作

> 前期需要的是：1、增加编号，2、增加表头格式化输出
>
> 随后应该注意到，每一个表的内部都应该有自己的数据打印方法。并且支持格式化数据。

#### 增加



（1）添加数据到文件中的大致思路

> 1. 读入数据
> 2. 将数据添加到链表的末尾
> 3. 将链表重新写入文件中去。

#### 修改

（1）修改数据功能实现

> - 用户输入待修改数据的ID
> - 获取到指定id的数据
> - 将数据的修改
> - 写入文件

#### 删除

（1）删除表中数据操作

> - 利用链表虚拟头结点的特点，输入待删除id
>
> - 链表通过断链操作，将数据更新
> - 将原本的数据文件清空，重新将链表的数据写入到文件当中去。

### 项目测试:增加多表功能

> - 目前微型数据库系统，只能通过复制源文件操作，修改对应信息，以达到增加多个表的功能
> - 创建一个头文件table_unit.h，将存储表信息和操作的文件拆分为通用部分和个体部分
> - 使用table_unit.h将通用代码保存，表示表信息的源文件只保留该表的特有信息。
> - 使用include宏，进行代码段的替换。

### 项目测试:交互流程功能

> - 用户进入微型数据库系统后，罗列表名，选择表的id号，进入到相应的表操作。通过提示信息完成业务的操作；
> - 当用户list查看表数据时，格式化输出表中的数据
> - 当用户add添加数据时，显示添加成功与否，并列出添加后的表数据
> - 当用户delete数据时，根据提示，输入待删除数据的id，删除后罗列出表中数据
> - 当用户修改数据时，选择对应表，选择表中的id输入修改的数据，提示操作结果

### 项目测试:切换多表功能

> - 用户选择返回上一层，回到选择表的界面，将根据id重新选择表以及对应的操作界面。

### 项目源码

**github：**[微型数据库_v1](https://github.com/OoWoOI/MDB)


