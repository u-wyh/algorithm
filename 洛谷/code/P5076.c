// https://www.luogu.com.cn/problem/P5076
// 题意：维护初始为空的互异整数集合
// 支持 q 次操作：查 x 排名、查第 x 小、查 x 前驱（无则 -2147483647）、查 x 后继（无则 2147483647）、插入不在集合中的 x。
// 数据范围：q <= 10^4，所有数绝对值在 10^9 以内。
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100010

int n,root,cnt,opt,x;

struct Node{
    int left,right,size,value,num;
    Node(int l,int r,int s,int v)
        :left(l),right(r),size(s),value(v),num(l){}
    Node(){}
}t[MAXN];

inline void update(int root){
    t[root].size=t[t[root].left].size+t[t[root].right].size+t[root].num;
}

int rank(int x,int root){
    if(root){

    }
}
