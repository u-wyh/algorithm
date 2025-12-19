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
