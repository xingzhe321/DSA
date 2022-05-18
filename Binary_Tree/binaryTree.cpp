/*************************************************************************
	> File Name: binaryTree.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed May  4 09:48:39 2022
 ************************************************************************/
#include<iostream>
#include<queue>
#include<stack>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBE -1
#define OVERFLOW -2
using namespace std;
#define TElemType char
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

//1.递归遍历算法
//先序遍历二叉树DLR
Status PreOrderTraverse(BiTree T){
    if(T == nullptr) return OK;
    else{
        visit(T);//访问根节点，visit函数单独实现，可以输出等操作
        PreOrderTraverse(T->lchild);//递归遍历左子树
        PreOrderTraverse(T->rchild);//递归遍历右子树
    }
    return OK;
}

//中序遍历二叉树LDR
Status InOrderTraverse(BiTree T){
    if(T == nullptr) return OK;
    else{
        InOrderTraverse(T->lchild);
        visit(T);
        InOrderTraverse(T->rchild);
    }
    return OK;
}


//后序遍历二叉树LRD
Status PostOrderTraverse(BiTree T){
    if(!T) return OK;
    else{
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        visit(T);
    }
    return OK;
}

//2.非递归遍历算法
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

//3.层次遍历算法
//定义队列结构
//C++写法 不用typedef
#define MAXQSIZE 100
struct SqQueue{
    BiTNode **base;//存储空间基地址
    int front, rear;//头尾指针
};
//初始化队列
Status InitQueue(SqQueue &Q){
    Q.base = new BiTNode*[MAXQSIZE];//**这里跟王卓课件写法不同，感觉她的有问题，也可能我写错了，未验证
    Q.front = Q.rear = 0;
    return OK;
}
//入队
Status EnQueue(SqQueue &Q, BiTNode *e){
    if((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}
//出队
Status DeQueue(SqQueue &Q, BiTNode *e){
    if(Q.front == Q.rear) return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}
//以下使用STL队列，内部实现如上
void LevelOrder(BiTNode *b){
    BiTNode *p = nullptr;
    queue<BiTNode*> q;
    if(!b) return;
    q.push(b);
    while(!q.empty()){
        p = q.front();
        q.pop();
        cout << p->data << " ";
        if(!p->lchild) q.push(p->lchild);
        if(!p->rchild) q.push(p->rchild);
    }
}

//4.先序遍历的方式建立二叉链表
Status CreateBiTree(BiTNode * &T){  //这里用指针引用作为形参 实参指针指向地址会跟随改变
    //顺序输入结点数据元素(字符)，#表示空
    char ch;
    cin >> ch;
    if (ch == '#') T = nullptr;
    else{
        //为根结点开辟空间
        //C: T = (BiTNode*) malloc (sizeof(BiTNode));
        T = new BiTNode;
        if (!T) exit(OVERFLOW);//空间分配失败
        T->data = ch;
        //递归创建左子树
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

//5.复制二叉树
void Copy(BiTNode *T, BiTNode *&NewT){
    if (T == nullptr) {
        NewT = nullptr;
        return;
    }
    else{
        NewT = new BiTNode;
        NewT->data = T->data;
        Copy(T->lchild, NewT->lchild);
        Copy(T->rchild, NewT->rchild);
    }//else
}//Copy()

//6.计算二叉树的深度
int Depth(BiTNode *T){
    if (!T) return 0;
    else{
        int m = Depth(T->lchild);
        int n = Depth(T->rchild);
        if (m > n) return m + 1;
        return n + 1;//else
    }//else
}

//7.统计二叉树中结点个数
int NodeCount(BiTNode *T){
    if (!T) return 0;
    return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}
//7.1补充 统计度为0(叶结点)的结点个数
int ZeroCount(BiTNode *T){
    if (!T) return 0;
    else if (T->lchild == nullptr && T->rchild == nullptr) return 1;
    else return ZeroCount(T->lchild) + ZeroCount(T->rchild);
}
//7.2补充 统计度为1的结点个数
int OneCount(BiTNode *T){
    if (!T) return 0;
    else if ((T->lchild && T->rchild == nullptr) || (T->lchild == nullptr && T->rchild)){
        return OneCount(T->lchild) + OneCount(T->rchild) + 1;
    }
    else return OneCount(T->lchild) + OneCount(T->rchild);
}
//7.3补充 统计度为2的结点个数
int TwoCount(BiTNode *T){
    if (!T) return 0;
    else if (T->lchild != nullptr && T->rchild != nullptr) return 1;
    else return TwoCount(T->lchild) + TwoCount(T->rchild);
}
//测试函数
//void test(){
//    BiTNode *T;
//    CreateBiTree(T);
//    BiTNode *NewT;
//    Copy(T, NewT);
//    int depth = Depth(NewT);
//    int node = NodeCount(NewT);
//    int zero = ZeroCount(NewT);
//    int one = OneCount(NewT);
//    int two = TwoCount(NewT);
//    cout << "复制树深度为 " << depth << endl;
//    cout << "结点个数 " << node << "\t叶子结点 " << zero << "\t度1结点 "
//         << one << "\t度2结点" << two << endl;
//}//先序AB##CD#E###样例通过

//树的存储结构
//1.双亲表示法 找双亲易 找孩子难
//结点
typedef struct PTNode {
    TElemType date;
    int parent;//双亲位置域
} PTNode;

//树
#define MAX_TREE_SIZE 100
typedef struct PTree {
    PTNode nodes[MAX_TREE_SIZE];
    int r, n;//根节点位置和结点个数
} PTree;

//2.孩子链表 找孩子易 找双亲难
//孩子结点
typedef struct CTNode {
    int child;//孩子结点位置
    struct CTNode* next;//指向下一个孩子结点
} *ChildPtr;
//双亲结点结构
typedef struct {
    TElemType data;
    ChildPtr firstchild;
} CTBox;
//树结构
typedef struct {
    CTBox nodes[MAX_TREE_SIZE];
    int r, n;//根节点位置和结点个数
} CTree;

//3.孩子兄弟表示法(二叉树表示法, 二叉链表表示法)(常用)
//每个结点的两个指针域分别指向其第一个孩子结点和下一个兄弟结点
typedef struct CSNode {
    TElemType data;
    struct CSNode* firstchild, * nextsibling;
} CSNode, *CSTree;
//树的存储结构结束


//int main(){
//    test();
//    return 0;
//}