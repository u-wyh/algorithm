#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MOD = 1e9+7;
const int INV2 = 500000004;
const int INV6 = 166666668;

int n,m;
int val[MAXN];

int tree[MAXN<<2];
int a[MAXN<<2],b[MAXN<<2],c[MAXN<<2];
int two[MAXN<<2];
int one[MAXN<<2];
int zero[MAXN<<2];

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
    tree[i]=(tree[i<<1]+tree[i<<1|1])%MOD;
}

int fun(int val){
    int ans=(((val*(val+1))%MOD)*(((2*val+1)*INV6)%MOD))%MOD;
    return ans;
}

void build(int l,int r,int i){
    a[i]=((fun(r)-fun(l-1))%MOD+MOD)%MOD;
    b[i]=((1+r)*r/2-(l-1)*l/2)%MOD;
    c[i]=r-l+1;
    if(l==r){
        tree[i]=val[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int t,int o,int z){
    tree[i]=(tree[i]+(t*a[i]%MOD)+(o*b[i]%MOD)+(z*c[i]%MOD))%MOD;
    two[i]=(two[i]+t)%MOD;
    one[i]=(one[i]+o)%MOD;
    zero[i]=(zero[i]+z)%MOD;
}

void down(int i){
    if(two[i]||one[i]||zero[i]){
        lazy(i<<1,two[i],one[i],zero[i]);
        lazy(i<<1|1,two[i],one[i],zero[i]);
        two[i]=one[i]=zero[i]=0;
    }
}

void update(int jobl,int jobr,int a,int b,int c,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,a,b,c);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,a,b,c,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,a,b,c,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        ans%=MOD;
        return ans;
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        val[i]=(val[i]+val[i-1])%MOD;
    }
    for(int i=1;i<=n;i++){
        val[i]=(val[i]+val[i-1])%MOD;
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r,d;
        op=read(),l=read(),r=read();
        if(l>r){
            swap(l,r);
        }
        if(op==1){
            d=read();
            int a,b,c;
            a=(d*INV2)%MOD;
            b=((a*(3-2*l))%MOD+MOD)%MOD;
            c=(a*((l-1)*(l-2)%MOD))%MOD;
            a=(a%MOD+MOD)%MOD;
            b=(b%MOD+MOD)%MOD;
            c=(c%MOD+MOD)%MOD;
            update(l,r,a,b,c,1,n,1);
            if(r<n){
                a=0;
                b=(d*(r-l+1))%MOD;
                c=d*((((((r-l+1)*(r-l+2)%MOD)*INV2%MOD)-((r-l+1)*r%MOD))%MOD+MOD)%MOD)%MOD;
                a=(a%MOD+MOD)%MOD;
                b=(b%MOD+MOD)%MOD;
                c=(c%MOD+MOD)%MOD;
                update(r+1,n,a,b,c,1,n,1);
            }
        }
        else{
            int ans=0;
            ans=((r-l+1)*query(n,n,1,n,1))%MOD;
            if(r>1){
                ans=(ans-query(max(1ll,l-1),r-1,1,n,1)+MOD)%MOD;
            }
            if(l<n){
                ans=(ans-query(max(n-r,1ll),n-l,1,n,1)+MOD)%MOD;
            }
            ans=(ans%MOD+MOD)%MOD;
            printf("%lld\n",ans);
        }
    }
    return 0;
}
/*
5 5
1 1 1 1 1
2 5 5
2 1 2
1 1 2 2
2 1 1
1 1 5 3
*/