#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e5+5;

int n,m;
int b[MAXN];
int pos[MAXN];

int tree[MAXN<<2];
int weight[MAXN<<2];

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
    weight[i]=(weight[i<<1]*weight[i<<1|1])%MOD;
    tree[i]=((tree[i<<1|1]*weight[i<<1])%MOD+tree[i<<1])%MOD;
}

void build(int l,int r,int i){
    if(l==r){
        weight[i]=b[l];
        tree[i]=(pos[l]*b[l])%MOD;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int jobi,int jobv,int l,int r,int i){
    if(l==r){
        weight[i]=jobv;
        tree[i]=(pos[jobi]*jobv)%MOD;
    }
    else{
        int mid=(l+r)>>1;
        if(jobi<=mid){
            update(jobi,jobv,l,mid,i<<1);
        }
        else{
            update(jobi,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        b[i]=read();
    }
    pos[n]=1;
    pos[n-1]=2;
    for(int i=n-2;i>=1;i--){
        pos[i]=(pos[i+1]*3)%MOD;
    }
    // for(int i=1;i<=n;i++){
    //     cout<<i<<":  "<<pos[i]<<endl;
    // }
    build(1,n,1);
    while(m--){
        int x,val;
        x=read(),val=read();
        update(x,val,1,n,1);
        printf("%lld\n",tree[1]);
    }
    return 0;
}