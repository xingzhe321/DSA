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

//算法5.快速排序
int Partition(SqList &L, int low, int high){
    //对顺序表L中的子表r[low, ..., high]进行一趟排序
    L.r[0] = L.r[low];//子表的low处做枢轴记录，存放到L.r[0]
    while (low < high){//从表的两端交替地向中间扫描
        while (low < high && L.r[high].key >= L.r[0].key) high--;
        L.r[low] = L.r[high];//右边搜索到的比枢轴记录小的记录移到低端
        while (low < high && L.r[low].key <= L.r[0].key) low++;
        L.r[high] = L.r[low];//左边搜索到的比枢轴记录大的记录移到高端
    } 
    L.r[low] = L.r[0];//枢轴记录到位
    return low;//返回枢轴位置
}

void QSort(SqList &L, int low, int high){
    if (low < high){
        int pivotloc = Partition(L, low, high);//返回第一次排序枢轴位置
        QSort(L, low, pivotloc - 1);//对左子表递归排序
        QSort(L, pivotloc + 1, high);//对右子表递归排序
    }
}

void QuickSort(SqList &L){//对顺序表L做快速排序
    QSort(L, 1, L.length);
}

//选择排序
//算法6.简单选择排序
void SelectSort(SqList &L){
    for (int i = 1; i < L.length; i++){//L.r[0]不用做监视哨可以i = 0; i < L.length - 1; i++
        int k  = i;//指向最小值位置
        for (int j = i + 1; i <= L.length; j++){
            if (L.r[j].key < L.r[k].key) k = j;
        }
        if (k != i) swap(L.r[i], L.r[k]);
    }
}

//算法7. 堆排序
/**
 * @brief 筛选法调整堆(大根堆)
 * 假设s + 1分支已经是堆，将s分支调整为以r[s]为根的大根堆
 * @param L 
 * @param s 根结点下标
 * @param m 最后一个结点下标
 */
void HeapAdjust(SqList &L, int s, int m){
    RedType rc = L.r[s];//根结点
    for (int j = 2 * s; j <= m; j *= 2){
        if (j < m && L.r[j].key < L.r[j + 1].key) j++;
        if (rc.key >= L.r[j].key) break;//是rc不是r[s]
        L.r[s] = L.r[j];
        s = j;
    }
    L.r[s] = rc;
}
/**
 * @brief 创建堆
 * 从最后一个叶子结点(n)的双亲结点(n/2)开始，往上(n/2 - 1、...、 1)
 * @param L 
 */
void CreatHeap(SqList &L){
    int n = L.length;
    for (int i = n / 2; i >= 1; i--){
        HeapAdjust(L, i, n);
    }
}

void HeapSort(SqList &L){
    CreatHeap(L);
    for (int i = L.length; i > 1; i--){
        swap(L.r[1], L.r[i]);
        HeapAdjust(L, 1, i - 1);
    }
}

//算法8.归并排序
/**
 * @brief 相邻两个有序子序列的归并 
 * 两个R归并成一个T
 * @param R 被归并子序列
 * @param T 归并子序列（合成后存放的）
 * @param low R1[low...]
 * @param mid R1[...mid] R2[mid + 1...]
 * @param high T[low...high]
 */
void Merge(RedType R[], RedType T[], int low, int mid, int high){
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high){
        if (R[i].key <= R[j].key) T[k++] = R[i++];//i指向的记录存入T中，同时移动i
        else T[k++] = R[j++];//这里严蔚敏教材上T[k] = R[j++]，应该写错了?
    }
    while (i <= mid) T[k++] = R[i++];
    while (j <= mid) T[k++] = R[j++];
}

void MSort(RedType R[], RedType T[], int low, int high){
    RedType S[MAXSIZE + 1];
    if (low == high) T[low] = R[low];
    else{
        int mid = (low + high) / 2;
        MSort(R, S, low, mid);
        MSort(R, S, mid + 1, high);
        Merge(S,T,low, mid, high);
    }
}

void MergeSort(SqList &L){
    MSort(L.r, L.r, 1, L.length);
}

//算法9.基数排序（桶排序）待补充
