/*************************************************************************
	> File Name: listUnion.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Apr 26 10:36:40 2022
 ************************************************************************/

#include<iostream>
using namespace std;

//线性表的合并，Lb中元素不存在La中则依次插入La表尾
void union(List &La, List &Lb)
{
    La_len = ListLength(La);
    Lb_len = ListLength(Lb);
    for(int i = 0; i < Lb_len; i++)
    {
        int e;
        GetElem(Lb, i, e);
        if(!LocateElem(La, e)) ListInsert(&La, ++La_len, e);
    }
}

//有序表的合并，值非递减有序排列
void MergeList_Sq(SqList LA, SqList LB, SqList &LC)
{
    LC.length = LA.length + LB.length;
    LC.elem = new ElemType[LC.length];

}
