#include <iostream>

using namespace std;

//顺序表查找
//顺序表存储元素中的关键字域和其他域类型 暂定义为int
#define KeyType int
#define InfoType int
//数据元素类型
struct ElemType{
    KeyType key;//关键字域
    InfoType otherinfo;//其他域
};
//顺序表类型
struct SSTable{
    ElemType *R;//存储空间基地址
    int length;//当前长度
};

//算法1.顺序查找
int Search_Seq(const SSTable &ST, const KeyType &key){
    for (int i = ST.length; i > 0; i--){//这里是ST.R[0]不用，使用的话就是i = ST.length - 1; i >= 0; i--
        if (ST.R[i].key == key){
            return i;
        }
    }
    return 0;//没找到返回0
}

//算法1.其他形式
int Search_Seqq(const SSTable &ST, const KeyType &key){
    int i = 0;
    for (i = ST.length; ST.R[i].key != key && i > 0; i--);
    return i;//不需要检查i > 0
}
//算法2.设置监视哨的顺序查找
//将待查关键字key存入ST.R[0]
int Search_Seqqq(const SSTable &ST, const KeyType &key){
    ST.R[0].key = key;
    int i = 0;
    for (i = ST.length; ST.R[i].key != key; i--);
    return i;
}

//算法3.二分查找
int Search_Bin(const SSTable &ST, const KeyType &key){
    int low = 1, high = ST.length;//给上下界初值
    while (high >= low){
        int mid = low + (high - low) / 2;
        if (ST.R[mid].key > key){
            high = mid - 1;
        }
        else if (ST.R[mid].key < key){
            low = mid + 1;
        }
        else return mid;
    }
    return 0;//未找到
}
//算法3.1 补充 二分查找的递归算法
int Search_Bin(const SSTable &ST, const KeyType &key, int low, int high){
    if (low > high) return 0;
    int mid = low + (high - low) / 2;
    if (ST.R[mid].key == key) return mid;
    else if (ST.R[mid].key > key) Search_Bin(ST, key, low, mid - 1);
    else Search_Bin(ST, key, mid + 1, high);
}
//[结束]顺序表查找

//树表查找
//二叉排序树：要么是空树，要么左子树比根结点小，右子树比根结点大
//二叉排序树性质：中序遍历是递增序列
//二叉排序树的存储结构
struct BSTNode{
    ElemType data;
    BSTNode *lch, *rch;
};
//BSTNode* T为一个二叉排序树
//算法4.二叉排序树查找
BSTNode * SearchBST(BSTNode *T, KeyType key){
    if ((!T) || T->data.key == key) return T;
    else if (T->data.key < key) SearchBST(T->rch, key);
    else SearchBST(T->lch, key);
}
//二叉排序树查找的时间复杂度最好O(logn) 最差O(n)

//算法5.二叉排序树插入
void InserBST(BSTNode *&T, ElemType e){
    if (!T){
        BSTNode *S = new BSTNode;
        S->data = e;
        S->lch = S->rch = nullptr;
        T = S;
    }
    else if (e.key < T->data.key) InserBST(T->lch, e);
    else InserBST(T->rch, e);
}

//算法6.二叉排序树的删除
void DeleteBST(BSTNode *&T, KeyType key){
    //p指向待删结点，f指向其双亲结点
    BSTNode *p = T, *f = nullptr;
    BSTNode *q = new BSTNode;
    //查找待删结点
    while (p){
        if (p->data.key == key) break;
        f = p;
        if (p->data.key > key) p = p->lch;
        else p = p->rch;
    }
    if (!p) return;//未找到
    //考虑三种情况
    if (p->lch != nullptr && p->rch != nullptr){//p所指结点左右子树均不为空
        q = p;//保存p前驱结点（下面的s）的双亲结点
        BSTNode *s = p->lch;//用来搜索p前驱结点，即p左子树的右下角结点
        while (s->rch){
            q = s;
            s = s->rch;
        }
        p->data = s->data;
        //接下来有两种情况(s可能有lch，一定没有rch)
        if (q == p) p->lch = s->lch;
        else q->rch = s->lch;
        delete s;
        return;
    }
    else if (!p->rch){//包含p->lch == nullptr 的可能
        q = p;
        p = p->lch;
    }
    else if (!p->lch){
        q = p;
        p = p->rch;
    }
    if (!f) T = p;//此时p在else if中已经是p->lch 或 p->rch
    else if (q == f->lch) f->lch = p;
    else f->rch = p;
    delete q;
}