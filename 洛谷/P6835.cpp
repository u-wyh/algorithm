#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 1e6+5;

int n,m;
int f[MAXN];
int g[MAXN];
int d[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

signed main()
{
    int id=read();
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        d[i]=1;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        d[u]++;
        addedge(u,v);
    }
    for(int i=1;i<=n;i++){
        f[i]=d[i];
        for(int ei=head[i];ei;ei=nxt[ei]){
            int v=to[ei];
            f[i]=(f[i]+g[i-1]-g[v-1])%MOD;
        }
        g[i]=(g[i-1]+f[i])%MOD;
    }
    g[n]=(g[n]+MOD)%MOD;
    cout<<g[n]<<endl;
    return 0;
}