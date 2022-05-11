/*************************************************************************
	> File Name: linkQueue.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat Apr 30 14:08:16 2022
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

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct LinkQueue
{
    QNode *front;
    QNode *rear;
}

//链队初始化
Status InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = new QNode;
    Q.front->next = nullptr;
    return OK;
}

//链队入队
Status EnQueue(LinkQueue &Q, QElemType e)
{
    QNode *p = new QNode;
    p->data = e;
    p->next = nullptr;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

//链队出队
Status DeQueue(LinkQueue &Q, QElemType &e)
{
    if(Q.front == Q.rear) return ERROR;
    //需要释放的是首元结点
    QNode *p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    //如果最后一个元素被删，队尾指针需要指向头结点
    if(p == Q.rear) Q.rear = Q.front;
    delete p;
    return OK;
}

//取队头元素
QElemType GetHead(LinkQueue Q)
{
    if(Q.front == Q.rear) exit(ERROR);
    return Q.front->next->data;
}

//销毁链队列
//从头结点开始，依次释放所有结点
Status DestroyQueue(LinkQueue &Q)
{
    //while(Q.front != Q.rear)
    //{
    //    QNode *p = Q.front->next;
    //    Q.front->next = p->next;
    //    if(Q.rear == p) Q.rear = Q.front;
    //    delete p;
    //}
    //delete Q.front;
    //return OK;
    //另写法，从front开始释放
    while(Q.front)
    {
        QNode *p = Q.front->next;
        delete Q.front;
        Q.front = p;
    }
    //如果头尾指针不再使用可以不用重新指向nullptr
    Q.front = Q.rear = nullptr;
}
