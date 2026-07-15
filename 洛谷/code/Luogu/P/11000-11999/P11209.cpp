#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXT = 30*MAXN;
const int BIT = 29;

int a[MAXN];
int b[MAXN];
int n,m,op;
int ans=0;

int tree[MAXT][2];
int en[MAXT];
int cnt=1;

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

void insert(int x){
    int cur=1;
    for(int i=BIT;i>=0;i--){
        int v=(a[x]>>i)&1;
        int u=(b[x]>>i)&1;
        if(u==1){
            if(tree[cur][v]==0){
                tree[cur][v]=++cnt;
            }
            en[tree[cur][v]]++;
            if(tree[cur][v^1]==0){
                tree[cur][v^1]=++cnt;
            }
            cur=tree[cur][v^1];
        }
        else{
            if(tree[cur][v]==0){
                tree[cur][v]=++cnt;
            }
            cur=tree[cur][v];
        }
    }
    en[cur]++;
}

void compute(int x){
    int cur=1;
    ans=0;
    for(int i=BIT;i>=0;i--){
        int path=(x>>i)&1;
        cur=tree[cur][path];
        if(cur==0){
            return ;
        }
        ans+=en[cur];
    }
    return ;
}

int main()
{
    op=read(),n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i++){
        b[i]=read();
    }
    for(int i=1;i<=n;i++){
        insert(i);
    }
    for(int i=1;i<=m;i++){
        int k=read();
        k^=(ans*op);
        compute(k);
        printf("%d\n",ans);
    }
    return 0;
}
