//
// Created by chase on 22-5-13.
//
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
//KMP实现串的模式匹配
//返回主串中模式串(子串)首次出现位置

//求next数组，将前缀表整体右移一位，首位置为-1
void getNext(int *&next, const string &s){
    //用指针i、j分别指向后缀、前缀的末尾
    int j = -1;
    int i = 0;
    next[0] = -1;
    while (i < s.size()){
        if (j == -1 || s[j] == s[i]){
            next[++i] = ++j;
        }
        else j = next[j];
    }//while
}

int Index_KMP(const string &s, const string &t){
    int *next = new int[t.size()];
    getNext(next, t);
    int i = 0, j = 0;
    while (i < s.size() && j < t.size()){
        if (s[i] == t[j]){
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }//while
    delete []next;
    if (j >= t.size()) return i - t.size();
    //if (j == t.size()) return i - j;应该也可以
    else return -1;//匹配失败
}
//测试
int main()
{
    string S, T;
    S = "aabaabaaf";
    T = "aabaaf";
    int pos = 0;
    cout << "S.size = " << S.size() << endl;
    cout << "T.size = " << T.size() << endl;
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    pos = Index_KMP(S, T);
    cout << "T in S pos = " << pos << endl;
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "KPM算法耗时" << time_used.count() << "ms" << endl;

    return 0;
}
