/*************************************************************************
	> File Name: sqQueue.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat Apr 30 12:57:46 2022
 ************************************************************************/
#include<iostream>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBE -1
#define OVERFLOW -2
using namespace std;
#define QElemType int
#define Status int

#define MAXQSIZE 100
//循环队列
//预留一个数组空间不使用
//(rear + 1) % MAXQSIZE = front;

typedef struct SqQueue
{
    QElemType *base;//存储空间的基地址
    int front;//头指针
    int rear;//尾指针
} SqQueue;

//初始化队列
Status InitQueue(SqQueue &Q)
{
    //Q.base = (QElemType *) malloc (MAXQSIZE * sizeof(QElemType));
    Q.base = new QElemType[MAXQSIZE];
    if(!Q.base) exit(OVERFLOW);
    Q.front = Q.rear = 0;
    return OK;
}

//求循环队列长度
int QueueLength(SqQueue Q)
{
    //if(Q.rear >= Q.front) return Q.rear - Q.front;
    //return MAXQSIZE - (Q.front - Q.rear);
    //合并为
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

//入队 在队尾插入一个新的元素
Status EnQueue(SqQueue &Q, QElemType e)
{
    if((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}

//出队 删除队头元素 保存被删除元素到e
Status DeQueue(SqQueue &Q, QElemType &e)
{
    if(Q.front == Q.rear) return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

//取队头元素
QElemType GetHead(SqQueue Q)
{
    if(Q.front != Q.rear) return Q.base[Q.front];
    else exit(ERROR);
}

