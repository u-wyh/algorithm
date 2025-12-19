#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 1e5+5;

int n,m;

int val[MAXN];

int tree[MAXN<<2];
int maxn[MAXN<<2];

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
    tree[i]=tree[i<<1]+tree[i<<1|1];
    maxn[i]=max(maxn[i<<1],maxn[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=val[l];
        maxn[i]=val[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]%=jobv;
        maxn[i]%=jobv;
    }
    else{
        int mid=(l+r)/2;
        if(jobl<=mid&&maxn[i<<1]>=jobv){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid&&maxn[i<<1|1]>=jobv){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void change(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=jobv;
        maxn[i]=jobv;
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

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r,v;
        op=read();
        if(op==1){
            l=read(),r=read();
            printf("%lld\n",query(l,r,1,n,1));
        }
        else if(op==2){
            l=read(),r=read(),v=read();
            update(l,r,v,1,n,1);
        }
        else{
            l=read(),v=read();
            change(l,v,1,n,1);
        }
    }
    return 0;
}