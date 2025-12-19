#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 2e5+5;

int n,m;
int nums[MAXN];
int ans;
int tree[MAXN<<2];
int tag[MAXN<<2];

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

inline void up(int i){
    tree[i]=max(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=nums[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }
}

void lazy(int i,int v){
    tree[i]=pow(tree[i],pow(2,v));
    tag[i]+=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void add(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,1);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void sub(int jobl,int jobr,int l,int r,int i){
    if(tree[i]==1){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        if(tag[i]>=1){
            tree[i]=sqrt(tree[i]);
            tag[i]--;
        }
        else{
            int mid=(l+r)/2;
            down(i);
            sub(jobl,jobr,l,mid,i<<1);
            sub(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            sub(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            sub(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void dfs(int l,int r,int i){
    if(l==r){
        ans+=tree[i];
    }
    else{
        int mid=(l+r)/2;
        down(i);
        dfs(l,mid,i<<1);
        dfs(mid+1,r,i<<1);
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r;
        op=read(),l=read(),r=read();
        if(op==1){
            add(l,r,1,n,1);
        }
        else{
            add(l,r,1,n,1);
        }
    }
    dfs(1,n,1);
    cout<<ans;
    return 0;
}