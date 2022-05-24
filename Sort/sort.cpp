#include <iostream>
using namespace std;

#define MAXSIZE 20//记录序列以顺序表存储，不超过20个
typedef int KeyType;//关键字设为int型
typedef int InfoType;

struct RedType
{
    KeyType key;
    InfoType otherinfo;
};

struct SqList
{
    RedType r[MAXSIZE + 1];//r[0]用作监视哨
    int length;
};
//插入排序
//算法1.直接插入排序算法 时间O(n2) 空间O(1)
void InsertSort(SqList &L){
    int i, j;
    for (i = 2; i <= L.length; i++){//i = 0用作监视哨，因此元素放置位置从L.r[1] = L.r[L.length]
        if (L.r[i].key < L.r[i - 1].key){
            L.r[0] = L.r[i];
            for ( j = i - 1; L.r[0].key < L.r[j].key; j--){
                L.r[j + 1] = L.r[j];
            }
            L.r[j + 1] = L.r[0];//插入正确位置（第一个L.r[j].key >= L.r[i]之后的位置）
        }
    }
}

//算法2.二分插入排序 时间O(n2) 空间O(1)
void BInsertSort(SqList &L){
    int i , j;
    for ( i = 2; i < L.length; i++){
        L.r[0] = L.r[i];
        int l = 1, r = i - 1;//左右界
        while (l <= r){
            int mid = (l + r) / 2;
            if (L.r[0].key < L.r[mid].key) r = mid - 1;
            else l = mid + 1;
        }//循环结束，r + 1为插入位置!![理解]不管哪种情况触发退出循环，r + 1位置都是最后一个>L.r[i].key的位置
        for (j = i - 1; i >= r + 1; j--){
            L.r[j + 1] = L.r[j];
        }
        L.r[r + 1] = L.r[0];
    }
}

//算法3.希尔排序

void ShellInsert(SqList &L, int dk){//对顺序表L做一次增量为dk的希尔插入排序
    int i, j;
    for (i = dk + 1; i <= L.length; i++){
        if (L.r[i].key < L.r[i - dk].key){
            L.r[0] = L.r[i];
            for ( j = i - dk; i > 0 && L.r[0].key < L.r[j].key; j -= dk){
                L.r[j + dk] = L.r[j];
            }
            L.r[j + dk] = L.r[0];
        }
    }
}

void ShellSort(SqList &L, int dt[], int t){//t = sizeof(dt) / sizeof(int)
    for (int k = 0; k < t; k++){
        ShellInsert(L, dt[k]);//dt[t - 1] = 1
    }
}

//交换排序
//算法4.冒泡排序
void BubbleSort(SqList &L){
    RedType x;
    for (int i = 1; i <= L.length - 1; i++){
        for (int j = 1; j <= L.length - i; j++){
            if (L.r[j + 1].key < L.r[j].key){
                x = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = x;
            }//if
        }//for
    }//for
}
//算法4.1冒泡排序的改进写法
void Bubble_Sort(SqList &L){
    RedType x;
    int m = L.length - 1;//等于王老师的 n - m
    int flag = 1;//标志某一趟排序是否发生交换
    while (m > 0 && flag == 1){
        flag = 0;//flag置为0，如果本次没有发生交换，则不会执行下一趟排序
        for (int j = 1; j <= m; j++){
            if (L.r[j].key > L.r[j + 1].key){
                flag = 1;
                x = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = x;
            }
        }
        m--;
    }
}