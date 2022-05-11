/*************************************************************************
	> File Name: binaryTree.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed May  4 09:48:39 2022
 ************************************************************************/
#include<iostream>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBE -1
#define OVERFLOW -2
using namespace std;
#define TElemType int
#define Status int

//二叉树的顺序存储结构
//按满二叉树结点层次编号，依次存放二叉树中的数据元素
#define MAXTSIZE 100
typedef TElemType SqBiTree[MAXTSIZE];
SqBiTree bt;//bt是数组变量

//二叉树的链式存储结构
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
//三叉链表
typedef struct TriTNode{
    TElemType data;
    struct TriTNode *lchild, *parent, *rchild;
} TriTNode, *TriTree;

//访问根节点
void visit(BiTNode *T)
{
    cout << T->data << endl;
}

//先序遍历二叉树DLR
Status PreOrderTraverse(BiTree T){
    if(T == nullptr) return OK;
    else{
        visit(T);//访问根节点，visit函数单独实现，可以输出等操作
        PreOrderTraverse(T->lchild);//递归遍历左子树
        PreOrderTraverse(T->rchild);//递归遍历右子树
    }
}

//中序遍历二叉树LDR
Status InOrderTraverse(BiTree T){
    if(T == nullptr) return OK;
    else{
        InOrderTraverse(T->lchild);
        visit(T);
        InOrderTraverse(T->rchild);
    }
}


//后序遍历二叉树LRD
Status PostOrderTraverse(BiTree T){
    if(!T) return OK;
    else{
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        visit(T);
    }
}

#define SElement BiTNode
//栈类 C++写法
typedef class StackNode{
public:
    SElement data;
    StackNode *next;
} *LinkStack;
//链栈初始化
Status InitStack(LinkStack &S){
    S = nullptr;//入栈后栈顶指针指向入栈结点
    return OK;
}
//判断链栈是否为空
Status StackEmpty(const LinkStack &S){
    if(!S) return TRUE;
    return FALSE;
}
//入栈
Status Push(LinkStack &S, const SElement &e){
    StackNode *r = new StackNode;
    r->data = e;
    r->next = S;
    S = r;
    return OK;
}
//出栈并保存值
Status Pop(LinkStack &S, SElement &e){
    if(!S) return ERROR;
    e = S->data;
    StackNode *r = S;
    S = S->next;
    delete r;
    return OK;
}

//中序遍历非递归算法
Status InOrderTraverse_S(BiTNode *T)
{
    BiTNode *p, *q;
    StackNode *S;
    InitStack(S);
    p = T;
    while(p || !StackEmpty(S)){
        if(p){
            Push(S, *p);
            p = p->lchild;
        }
        else{
            Pop(S, *q);
            cout << q->data << " ";
            p = q->rchild;
        }
    }
    cout << endl;
    return OK;
}
