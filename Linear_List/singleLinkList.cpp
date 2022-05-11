/*************************************************************************
	> File Name: singleLinkList.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Apr 24 16:32:02 2022
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

typedef struct ListNode{
    ElemType data;
    struct ListNode *next;
} ListNode, *LinkList;

Status InitList(LinkList &L)
{
    L = new ListNode;//L = (LinkList) malloc (sizeof(ListNode))
    L->next = NULL;
    return OK;
}

//判断链表是否为空
//=头结点指针域是否为空
int ListEmpty(LinkList &L)
        L->next = p;
{
    if(L->next)
    {
        return 0;
    }
    return 1;//为空
}

//单链表的销毁
//从头指针开始依次释放，依次释放所有结点
int DestroyList(LinkList &L)
{
    if(L = NULL) return 0;
    while(L)
    {
        ListNode *p = L;
        L = L->next;
        delete p;
    }
    return 1;
}

//清空单链表
//依次释放所有结点，并将结点指针域设置为空
int clearList(LinkList &L)
{
    if(L == NULL || L->next == NULL) return 0;
    ListNode *p, *q;
    p = L->next;
    while(p)
    {
        q = p;
        p = p->next;
        delete q;
    }
    L->next = NULL;
    return 1;
}

//求单链表表长
//从首元结点开始，依次计数所有结点
int ListLength(LinkList &L)
{
    if(L == NULL || L->next == NULL) return 0;
    ListNode *p = L->next;
    int ind = 0;
    while(p)
    {
        ind++;
        p = p->next;
    }
    return ind;
}

//单链表取值，i位置值，用e返回元素
Status GetElem(LinkList L, int i, ElemType &e)
{
    ListNode *p = L->next;
    int ind = 1;
    while(p && ind < i)
    {
        p = p->next;
        ind++;
    }
    if(!p || ind > i) return ERROR;
    e = p->data;
    return OK;
}

//单链表按值查找 返回地址
ListNode *LocateElem(LinkList L, ElemType e)
{
    ListNode *p = L->next;
    while(p && p->data != e)
    {
        p = p->next;
    }
    if(!p) return ERROR;
    return p;
}

//单链表按值查找 返回位置
int LocateElem_L(LinkList L,ElemType e)
{
    ListNode *p = L->next;
    int ind = 1;
    while(p && p->data != e)
    {
        p = p->next;
        ind++;
    }
    if(!p) return ERROR;
    return ind;
}

//单链表的插入
Status ListInsert(LinkList &L, int i, ElemType e)
{
    ListNode *p = L;
    int ind = 0;
    while(p && ind < i-1)
    {
        p = p->next;
        ind++;
    }
    if(p || ind > i-1) return ERROR;
    ListNode *q = new ListNode;
    q->data = e;
    q->next = p->next;
    p->next = q;
    return OK;
}

//单链表的删除
Status ListDelete(LinkList &L, int i)
{
    ListNode *p = L;
    int ind = 0;//有可能删首元 所以p要从i=1-1开始
    while(p->next && ind < i-1)
    {
        p = p->next;
        ind++;
    }
    if(!p->next || ind > i-1) return ERROR;
    ListNode *q = p->next;
    p->next = q->next;
    delete q;
    return OK;
}

//创建单链表 头插
void CreateList_H(LinkList &L, int n)
{
    L = new ListNode;
    L->next = nullptr;
    for(int i = n; n > 0; i--)
    {
        ListNode *p = new ListNode;
        cin >> p->data;
        p->next = L->next;
        L->next = p;
    }
}

//创建单链表 尾插
void CreateList_R(LinkList &L, int n)
{
    L = new ListNode;
    L->next = nullptr;
    ListNode *r = L;
    for(int i = 0; i < n; i++)
    {
        ListNode *p = new ListNode;
        cin >> p->data;
        p->next = nullptr;
        r->next = p;
        r = p;
    }
}

//带尾指针循环链表的合并
ListNode *Connect(LinkList Ta, LinkList Tb)
{
    ListNode *p = Ta->next;
    Ta->next = Tb->next->next;
    delete Tb->next;
    Tb->next = p;
    return Tb;
}

