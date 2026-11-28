// https://www.luogu.com.cn/problem/P4137
// 题意：第一行输入数组长度 n 和询问数 m，
// 第二行输入非负整数数列 a_1..a_n，
// 接下来 m 行每行输入区间 [l, r]。
// 每次询问区间 [l, r] 内最小的未出现过的自然数（mex，从 0 开始）。
// 输出 m 行，每行一个整数表示每个询问的答案。
// 数据范围：1 <= n, m <= 2*10^5，
// 1 <= l <= r <= n，0 <= a_i <= 2*10^5。
// 难度评分：2300（洛谷分级换算）
// 算法标签：可持久化线段树、线段树上二分
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = MAXN*30;

int n,m;
int val[MAXN];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int lateleft[MAXT];
int cnt;

int build(int l,int r){
    int rt=++cnt;
    lateleft[rt]=0;
    if(l<r){
        int mid=(l+r)>>1;
        ls[rt]=build(l,mid);
        rs[rt]=build(mid+1,r);
    }    
    return rt;
}

void up(int i){
    lateleft[i]=min(lateleft[ls[i]],lateleft[rs[i]]);
}

int insert(int jobv,int pos,int l,int r,int i){
    int rt=++cnt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    lateleft[rt]=lateleft[i];
    if(l==r){
        lateleft[rt]=pos;
    }
    else{
        int mid=(l+r)>>1;
        if(jobv<=mid){
            ls[rt]=insert(jobv,pos,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(jobv,pos,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

void prepare(){
    root[0]=build(0,n);
    for(int i=1;i<=n;i++){
        if(val[i]<=n){
            root[i]=insert(val[i],i,0,n,root[i-1]);
        }
        else{
            root[i]=root[i-1];
        }
    }
}

int query(int limit,int l,int r,int i){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        if(lateleft[ls[i]]<limit){
            return query(limit,l,mid,ls[i]);
        }
        else{
            return query(limit,mid+1,r,rs[i]);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    prepare();

    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        cout<<query(l,0,n,root[r])<<endl;
    }
    return 0;
}