#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
struct node{
    long long num,den;//斜率的表示  分子分母
    int cnt;
    int extra;
}tree[MAXN<<2];

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

int query(long long prenum,long long preden,int l,int r,int i){
    if(tree[i].num*preden<=tree[i].den*prenum){
        return 0;
    }
    if(l==r){
        return 1;
    }
    else{
        int mid=(l+r)>>1;
        if(tree[i<<1].num*preden<=tree[i<<1].den*prenum){
            return query(prenum,preden,mid+1,r,i<<1|1);
        }
        else{
            return query(prenum,preden,l,mid,i<<1)+tree[i].extra;
        }
    }
}

void up(int l,int r,int i){
    long long lnum=tree[i<<1].num,lden=tree[i<<1].den;
    long long rnum=tree[i<<1|1].num,rden=tree[i<<1|1].den;

    if(lnum*rden<=rnum*lden){
        tree[i].num=rnum,tree[i].den=rden;
    }
    else{
        tree[i].num=lnum,tree[i].den=lden;
    }
    int mid=(l+r)>>1;
    tree[i].extra=query(lnum,lden,mid+1,r,i<<1|1);
    tree[i].cnt=tree[i<<1].cnt+tree[i].extra;
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i].num=jobv;
        tree[i].den=l;
        tree[i].cnt=1;
        tree[i].extra=0;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        up(l,r,i);
    }
}

void build(int l,int r,int i){
    tree[i].num=0,tree[i].den=1;
    tree[i].cnt=0;
    tree[i].extra=0;
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

int main()
{
    n=read(),m=read();
    build(1,n,1);
    while(m--){
        int x,y;
        x=read(),y=read();
        update(x,y,1,n,1);
        cout<<tree[1].cnt<<endl;
    }
    return 0;
}