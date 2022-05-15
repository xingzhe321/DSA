/*************************************************************************
	> File Name: string.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun May  1 18:40:27 2022
 ************************************************************************/
#include<iostream>
#include<chrono>
#include<string>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBE -1
#define OVERFLOW -2
using namespace std;
#define ElemType int
#define Status int

#define MAXLEN 100
//串的顺序存储结构
typedef struct SString{
    char ch[MAXLEN];
    int length;
} SString;
//串的顺序存储结构堆式写法
typedef struct HString{
    char* ch;
    int length;
} HString;

//串的块链结构
#define CHUNKSIZE 80
typedef struct Chunk{
    char ch[CHUNKSIZE];
    struct Chunk *next;
} Chunk;
typedef struct LString{
    Chunk *head, *tail;//头指针和尾指针，可以选择性包含
    int curlen;//串的当前长度
} LString;

//串的模式匹配算法
//确定主串所含子串（模式串）第一次出现的位置
//不存在则返回0
//Brute-Force算法
int Index_BF(const string &S, const string &T)
{
    int i = 0, j = 0;
    while(i < S.size() && j < T.size())
    {
        if(S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if(j >= T.size())
    {
        return i - T.size();
    }
    else return 0;
}//时间复杂度O(m*n)

//KMP算法
//求next数组,默认版本
//5.13修改为static函数，使函数仅在本文件可见
static void getNext(int *next, const string &s)
{
    //指针i、j,分别指向后缀和前缀末尾位置
    //step1初始化
    int j = 0;
    next[0] = 0;
    //step2处理前后缀不相同情况
    for(int i = 1; i < s.size(); i++)
    {
        //j可能不止回退一位，所有要用while循环
        //if(s[i] != s[j] && j > 0)
        //{
        //    j = next[j-1];
        //}
        while(j > 0 && s[i] != s[j])
        {
            j = next[j-1];
        }
        //step3处理前后缀相同情况
        if(s[i] == s[j])
        {
            j++;
        }
        next[i] = j;
    }
}
//求next数组，右移一位版本，首位为-1
void getNxt(int * nxt, const string &s)
{
    /*
    //指针i指向后缀末尾，j指向前缀末尾
    //step1初始化
    int j = -1;
    nxt[0] = -1;
    //step2处理前后缀不同情况
    for(int i = 1; i < s.length; i++)
    {
        while(j >= 0 && s[i-1] != s[j])
        {
            j = nxt[j];
        }
        //step3处理前后缀相同情况
        j++;
        nxt[i] = j;
    }
    */
    //换个写法
    nxt[0] = -1;
    int i = 0, j = -1;
    while(i < s.size())
    {
        if(j == -1 || s[i] == s[j])
        {
            i++;
            j++;
            nxt[i] = j;
        }
        else
        {
            j = nxt[j];
        }
    }
}

//KMP模式匹配
//修改：增加static关键字
static int Index_KMP(string &S, string &T)
{
    int next[T.size()];
    getNxt(next, T);
    //for (auto &i : next)
    //{
    //    cout << i << endl;
    //}
    int i = 0, j = 0;
    while(i < S.size() && j < T.size())
    {
        if(S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if(j >= T.size()) return i - j;
    else return 0;
}


//测试案例
int main()
{
    string S, T;
    S = "aabaabaaf";
    T = "aabaaf";
    int pos = 0;
    cout << "S.size = " << S.size() << endl;
    cout << "T.size = " << T.size() << endl;
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    pos = Index_BF(S, T);
    cout << "T in S pos = " << pos << endl;
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "BF算法耗时" << time_used.count() << "ms" << endl;
    t1 = chrono::steady_clock::now();
    pos = Index_KMP(S, T);
    cout << "T in S pos = " << pos << endl;
    t2 = chrono::steady_clock::now();
    time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "KPM算法耗时" << time_used.count() << "ms" << endl;

    return 0;
}
