/*************************************************************************
	> File Name: sqStack.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu Apr 28 10:46:48 2022
 ************************************************************************/

#include<iostream>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBE -1
#define OVERFLOW -2
using namespace std;
#define SElemType int
#define Status int

#define MAXSIZE 100

typedef struct
{
    SElemType *base;//栈底
    SElemType *top;//栈顶
    int stacksize;//栈可用最大容量
} SqStack;

//初始化
//动态分配最大容量为MAXSIZE的数组空间, base指向空间的基地址
//top初始为base，表示栈顶为空
//stacksize置为MAXSIZE
Status InitStack(SqStack &S)
{
    S.base = new SElemType[MAXSIZE];
    if(!S.base) exit(OVERFLOW);//base指向nullptr表示存储分配失败
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}

//入栈
//栈顶插入新元素
//指向同一数组的元素指针可以直接相减，结果为所指向元素之间间隔
Status Push(SqStack &S, SElemType e)
{
    if(S.top - S.base == S.stacksize) return ERROR;//栈满
    *S.top++ = e;
    return OK;
}

//出栈
//栈顶元素删除
//判断栈是否为空,用e返回值
Status Pop(SqStack &S, SElemType &e)
{
    if(S.top == S.base) return ERROR;//栈空
    e = *--S.top;
    return OK;
}

//取栈顶元素
SElemType GetTop(SqStack S)
{
    if(S.top != S.base)
    return *(S.top - 1);
}

//判断栈是否为空
bool StackEmpty(SqStack S)
{
    if(S.top == S.false) return true;
    return false;
}

//求顺序栈长度
int StackLength(SqStack S)
{
    return S.top - S.base;
}

//清空顺序栈
Status ClearStack(SqStack &S)
{
    if(S.base) S.top = S.base;
    return OK;
}

//销毁顺序栈
Status DestroyStack(SqStack &S)
{
    if(S.base)
    {
        delete S.base;
        S.stacksize = 0;
        S.top = S.base = nullptr;
    }
    return OK;
}
