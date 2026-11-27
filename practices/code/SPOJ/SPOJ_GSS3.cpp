// https://www.spoj.com/problems/GSS3/
// 题意：给长为 N 的序列 A，支持 M 次操作。
// 0 x y 将 A[x] 修改为 y。
// 1 x y 查询 [x, y] 的最大非空连续子段和。
// 输出：逐行输出 1 类查询的答案。
// 数据范围：1 <= N, M <= 5*10^4，
// -10^4 <= A_i, y <= 10^4。
// 修改满足 1 <= x <= N。
// 查询满足 1 <= x <= y <= N。
// 算法标签：线段树
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50005;

struct node{
    int l=INT_MIN,r=INT_MIN,all=INT_MIN,sum=INT_MIN;
}tree[MAXN<<2];
int n,m;
int arr[MAXN];

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

node up(node l,node r){
    node u;
    u.all=max(max(l.all,r.all),l.r+r.l);
    u.sum=l.sum+r.sum;
    u.l=max(l.l,l.sum+r.l);
    u.r=max(r.r,r.sum+l.r);
    return u;
}

void build(int l,int r,int i){
    if(l==r){
        tree[i].l=tree[i].r=tree[i].all=tree[i].sum=arr[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=up(tree[i<<1],tree[i<<1|1]);
    }
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i].l=tree[i].r=tree[i].all=tree[i].sum=jobv;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        tree[i]=up(tree[i<<1],tree[i<<1|1]);
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        if(jobl<=mid&&jobr>mid){
            return up(query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobl<=mid){
            return query(jobl,jobr,l,mid,i<<1);
        }
        else{
            return query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    build(1,n,1);
    m=read();
    for(int i=1;i<=m;i++){
        int op,u,v;
        op=read(),u=read(),v=read();
        if(op==1){
            cout<<query(u,v,1,n,1).all<<endl;
        }
        else{
            update(u,v,1,n,1);
        }
    }
    return 0;
}