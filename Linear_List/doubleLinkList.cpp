/*************************************************************************
	> File Name: doubleLinkList.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Apr 26 09:53:32 2022
 ************************************************************************/

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

typedef struct DuLNode{
    ElemType data;
    struct DuLNode *prior, *next;
}DuLNode, *DuLinkList;

//双向链表的插入
Status ListInsert_DuL(DuLinkList &L, int i, ElemType e)
{
    DuLNode *p = L->next;
    int ind = 1;
    while(p && ind < i-1)
    {
        p = p->next;
        ind++;
    }
    if(!p || ind > i-1) return ERROR;
    DuLNode *s = new DuLNode;
    s->data = e;
    s->prior = p->prior;
    p->prior->next = s;
    s->next = p;
    p->prior = s;
    return OK;
}

//双向链表的删除
Status ListDelete_Dul(DuLinkList &L, int i)
{
    DuLNode *p = L;
    int ind = 1;
    while(p && ind < i-1)
    {
        p = p->next;
        ind++;
    }
    if(!p || ind > i-1) return ERROR;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    delete p;
    return OK;
}
