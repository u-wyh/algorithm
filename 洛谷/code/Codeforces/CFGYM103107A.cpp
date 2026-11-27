// https://codeforces.com/gym/103107/problem/A
// 题意：维护长为 n 的序列，支持 m 次操作：
// 区间按位与、单点赋值以及区间最大值查询。
// 输出：对每次查询输出一行区间最大值。
// 数据范围：1 <= N, M <= 4*10^5，
// 1 <= a_i, v <= 2^30 - 1，
// 1 <= l, r, x <= n，至少有一次查询。
// 算法标签：线段树、位运算
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e5+5;

int n,m;
int val[MAXN];
char s[3];

int tree[MAXN<<2];
int maxx[MAXN<<2];

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

void up(int i){
    tree[i]=(tree[i<<1]|tree[i<<1|1]);
    maxx[i]=max(maxx[i<<1],maxx[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=maxx[i]=val[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void change(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=jobv;
        maxx[i]=jobv;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            change(pos,jobv,l,mid,i<<1);
        }
        else{
            change(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if((tree[i]&jobv)==tree[i]){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        if(l==r){
            tree[i]=tree[i]&jobv;
            maxx[i]=tree[i];
            return;
        }
        int mid=(l+r)>>1;
        update(jobl,jobr,jobv,l,mid,i<<1);
        update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        up(i);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return maxx[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        scanf("%s",s);
        if(s[0]=='A'){
            int l,r,v;
            l=read(),r=read(),v=read();
            update(l,r,v,1,n,1);
        }
        else if(s[0]=='U'){
            int u,v;
            u=read(),v=read();
            change(u,v,1,n,1);
        }
        else{
            int l,r;
            l=read(),r=read();
            printf("%d\n",query(l,r,1,n,1));
        }
    }
    return 0;
}