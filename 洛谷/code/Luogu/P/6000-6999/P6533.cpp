#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MOD = 1e4+7;
const int MAXM = 21;

int n,m,c;
int a[MAXN],b[MAXN];
int tree[MAXN<<2][MAXM];

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

void up(int u){
    for(int i=0;i<=c;i++){
        tree[u][i]=0;
    }
    for(int i=0;i<=c;i++){
        for(int j=0;j<=c;j++){
            tree[u][min(i+j,c)] = (tree[u][min(i+j,c)] + (tree[u<<1][i] * tree[u<<1|1][j]) % MOD) % MOD;
        }
    }
}

void build(int l,int r,int i){
    if(l==r){
        tree[i][0]=b[l];
        tree[i][1]=a[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int pos,int l,int r,int i){
    if(l==r){
        tree[i][0]=b[l];
        tree[i][1]=a[l];
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,l,mid,i<<1);
        }
        else{
            update(pos,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int main()
{
    n=read(),c=read();
    for(int i=1;i<=n;i++){
        a[i]=read()%MOD;
    }
    for(int i=1;i<=n;i++){
        b[i]=read()%MOD;
    }
    build(1,n,1);
    m=read();
    for(int i=1;i<=m;i++){
        int p=read();
        a[p]=read()%MOD,b[p]=read()%MOD;
        update(p,1,n,1);
        cout<<((tree[1][c]%MOD)+MOD)%MOD<<endl;
    }
    return 0;
}