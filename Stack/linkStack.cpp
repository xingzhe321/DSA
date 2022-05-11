/*************************************************************************
	> File Name: linkStack.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu Apr 28 14:27:12 2022
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

typedef struct StackNode
{
    SElemType data;
    struct StackNode *next;
} StackNode, *LinkStack;
//链表和链栈的next指针指向相反

//初始化
Status InitStack(LinkStack &S)
{
    //不需要头结点
    S->next = nullptr;
    return OK;
}

//判断链栈是否为空
Status StackEmpty(LinkStack S)
{
    if(S == nullptr) return TRUE;
    return FALSE;
}

//入栈
Status Push(LinkStack &S, SElemType e)
{
    StackNode *p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
    return OK;
}

//出栈
Status pop(LinkStack &S, SElemType &e)
{
    if(!S) return ERROR;
    e = S->data;
    StackNode *p = S;
    S = S->next;
    delete p;
    return OK;
}

//取栈顶元素
SElemType GetTop(LinkStack S)
{
    if(!S) return ERROR;
    return S->data;
}
