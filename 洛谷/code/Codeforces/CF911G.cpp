// https://codeforces.com/problemset/problem/911/G
// 题意：长为 n 的数组 a，q 次操作每次给 l, r, x, y。
// 规则：将区间 [l, r] 内所有等于 x 的元素改为 y。
// 输出：全部操作结束后输出最终数组。
// 数据范围：1 <= n, q <= 2*10^5，
// 1 <= a_i, x, y <= 100。
// 1 <= l <= r <= n。
// 算法标签：线段树分裂、线段树合并
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = 2e7+5;

int n,q;

int val[MAXN];

int root[101];
int cnt;
int ls[MAXT],rs[MAXT];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int add(int pos,int l,int r,int i){
    int rt=i;
    if(i==0){
        rt=++cnt;
    }
    if(l==r){
        return rt;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            ls[rt]=add(pos,l,mid,ls[rt]);
        }
        else{
            rs[rt]=add(pos,mid+1,r,rs[rt]);
        }
        return rt;
    }
}

int merge(int u,int v){
    if(u==0||v==0){
        return u+v;
    }
    ls[u]=merge(ls[u],ls[v]);
    rs[u]=merge(rs[u],rs[v]);
    return u;
}

pair<int,int> update(int jobl,int jobr,int l,int r,int u,int v){
    if(u==0){
        return {u,v};
    }
    if(jobl<=l&&r<=jobr){
        v=merge(u,v);
        u=0;
        return {u,v};
    }
    else{
        int mid=(l+r)/2;
        if(v==0){
            v=++cnt;
        }
        if(jobl<=mid){
            pair<int,int>tmp=update(jobl,jobr,l,mid,ls[u],ls[v]);
            ls[u]=tmp.first;
            ls[v]=tmp.second;
        }
        if(jobr>mid){
            pair<int,int>tmp=update(jobl,jobr,mid+1,r,rs[u],rs[v]);
            rs[u]=tmp.first;
            rs[v]=tmp.second;
        }
        return {u,v};
    }
}

void compute(int l,int r,int i,int op){
    if(i==0){
        return ;
    }
    if(l==r){
        val[l]=op;
    }
    int mid=(l+r)/2;
    compute(l,mid,ls[i],op);
    compute(mid+1,r,rs[i],op);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        root[val[i]]=add(i,1,n,root[val[i]]);
    }
    q=read();
    for(int i=1;i<=q;i++){
        int l,r,u,v;
        l=read(),r=read(),u=read(),v=read();
        if(u==v){
            continue;
        }
        pair<int,int>tmp=update(l,r,1,n,root[u],root[v]);
        root[u]=tmp.first;
        root[v]=tmp.second;
    }
    for(int i=1;i<=100;i++){
        compute(1,n,root[i],i);
    }
    for(int i=1;i<=n;i++){
        printf("%d ",val[i]);
    }
    return 0;
}