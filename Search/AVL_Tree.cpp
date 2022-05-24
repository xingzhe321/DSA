#include <iostream>

using namespace std;
//AVL结点类定义
template<class Key, class E>
class AVLNode {
private:
    Key key;
    E value;
    AVLNode<Key, E> *lch;
    AVLNode<Key, E> *rch;
    AVLNode<Key, E> *parent;
public:
    //AVLNode默认构造
    AVLNode() : lch(nullptr), rch(nullptr), parent(nullptr) {}
    //AVLNode有参构造
    AVLNode(Key _key, E _value, AVLNode<Key, E> *_lch, AVLNode<Key, E> *_rch, AVLNode<Key, E> *_parent) :
            key(_key), value(_value), lch(_lch), rch(_rch), parent(_parent) {}

    //标志是否叶子结点
    bool isLeaf() {return !lch && !right};

    //设置元素
    void setKey(Key set) {key = set};
    Key getKey() const {return key};

    void setValue(E set) {value = set};
    E getValue() const {return value};

    void setLch(AVLNode<Key, E> *set) {lch = set};
    AVLNode<Key, E> * getLch() {return lch};

    void setRch(AVLNode<Key, E> *set) {rch = set};
    AVLNode<Key, E> * getRch() {return rch};

    void setParent(AVLNode<Key, E> *set) {parent = set};
    AVLNode<Key, E> * getParent() {return parent};
};

template<class Key, class E>
class AVLTree {
private:
    AVLNode<Key, E> *root;//AVL树的根节点
    //AVL树的清除
    void clear(AVLNode<Key, E> *&r){
        if (r == nullptr) return;
        else {
            clear(r->getLch());
            clear(r->getRch());
            delete r;
        }
    }
    //中序遍历AVL树

public:
    //默认构造，类内声明，类外实现
    AVLTree();
    //析构函数
    ~AVLTree() {clear(root);}
};

//带模板的类外实现太麻烦了，只写构造函数，其余写在类内
template<class Key, class E>
AVLTree<Key, E>::AVLTree() {root = nullptr;}
