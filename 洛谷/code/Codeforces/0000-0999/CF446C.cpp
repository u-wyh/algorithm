#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MOD = 1e9+9;

int n,m;
int fib[MAXN];
int inv[MAXN];//负数斐波那契数列
int val[MAXN];

int tmp1[MAXN<<2];
int tmp2[MAXN<<2];
int tag1[MAXN<<2];
int tag2[MAXN<<2];
int tree[MAXN<<2];

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

void prepare(){
    fib[1]=fib[2]=1;
    for(int i=3;i<=n+2;i++){
        fib[i]=(fib[i-1]+fib[i-2])%MOD;
    }
    fib[0]=0;
    inv[1]=1;
    inv[2]=-1;
    for(int i=3;i<=n+2;i++){
        inv[i]=(inv[i-2]-inv[i-1])%MOD;
    }
}

void up(int i){
    tree[i]=(tree[i<<1]+tree[i<<1|1])%MOD;
}

void build(int l,int r,int i){
    tag1[i]=0,tag2[i]=0;
    if(l==r){
        tmp1[i]=fib[l+1];
        tmp2[i]=fib[l];
        tree[i]=val[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tmp1[i]=(tmp1[i<<1]+tmp1[i<<1|1])%MOD;
        tmp2[i]=(tmp2[i<<1]+tmp2[i<<1|1])%MOD;
        tree[i]=(tree[i<<1]+tree[i<<1|1])%MOD;
    }
    // cout<<i<<": "<<l<<' '<<r<<' '<<tree[i]<<' '<<tmp1[i]<<' '<<tmp2[i]<<endl;
}

void lazy(int i,int v1,int v2){
    tag1[i]=(tag1[i]+v1)%MOD;
    tag2[i]=(tag2[i]+v2)%MOD;
    tree[i]=(tree[i]+v1*tmp1[i]%MOD+v2*tmp2[i]%MOD)%MOD;
}

void down(int i){
    if(tag1[i]||tag2[i]){
        lazy(i<<1,tag1[i],tag2[i]);
        lazy(i<<1|1,tag1[i],tag2[i]);
        tag1[i]=0;
        tag2[i]=0;
    }
}

void add(int jobl,int jobr,int v1,int v2,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,v1,v2);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,v1,v2,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,v1,v2,mid+1,r,i<<1|1);
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
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans=(ans+query(jobl,jobr,mid+1,r,i<<1|1))%MOD;
        }
        return ans;
    }
}

signed main()
{
    n=read(),m=read();
    prepare();
    // for(int i=0;i<=n;i++){
    //     cout<<fib[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=0;i<=n;i++){
    //     cout<<inv[i]<<' ';
    // }
    // cout<<endl;
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r;
        op=read(),l=read(),r=read();
        if(op==1){
            add(l,r,inv[l-1],inv[l],1,n,1);
        }
        else{
            printf("%lld\n",(query(l,r,1,n,1)%MOD+MOD)%MOD);
        }
    }
    return 0;
}