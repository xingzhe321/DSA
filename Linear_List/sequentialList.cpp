//
// Created by chase on 22-4-26.
//
#include<iostream>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBE -1
#define OVERFLOW -2
using namespace std;
#define ElemType int
#define Status int

#define MAXSIZE 100

typedef struct SqList
{
    ElemType *elem;//存储空间的基地址
    int length;
} SqList;

//初始化：elem指向数组空间首地址
Status InitList(SqList &L)
{
    L.elem = new ElemType[MAXSIZE];//L.elem可以销毁 属于动态分配内存
    if (!L.elem) exit(OVERFLOW);//存储分配失败退出
    L.length = 0;
    return OK;
}

//取值：获取顺序表中第i个数据元素的值
Status GetElem(SqList L, int i, ElemType &e)
{
    if (i < 1 || i > MAXSIZE) return ERROR;
    e = L.elem[i-1];
    return OK;
}

//查找：查找顺序表中第一个与e相等的元素，返回位置
int LocateElem(SqList L, ElemType e)
{
    for (int i = 0; i < MAXSIZE; ++i)
    {
        if (L.elem[i] == e) return i+1;
    }
    return 0;
}

//插入：在顺序表第i个元素位置插入元素e
Status ListInsert(SqList &L, int i, ElemType e)
{
    if (i < 1 || i > L.length+1) return ERROR;
    if (L.length == MAXSIZE) return ERROR;
    for (int j = L.length; j > i-1; j--)
    {
        L.elem[j] = L.elem[j-1];
    }
    L.elem[i-1] = e;
    L.length++;
    return OK;
}

//删除：将顺序表第i个元素删去
Status ListDelete(SqList &L, int i)
{
    if (i < 1 || i > L.length) return ERROR;
    for (int j = i-1; j < L.length-1; ++j)
    {
        L.elem[j] = L.elem[j+1];
    }
    L.length--;
    return OK;
}