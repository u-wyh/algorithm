#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e8+7;
const int MAXN = 1e6+5;

int n,op;

int cnt=1;
int head[MAXN];
int to[MAXN<<1];
int Next[MAXN<<1];

int f[MAXN],g[MAXN];

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

inline void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
            f[u]=(f[u]*g[v]+f[v]*g[u]+f[u]+f[v])%MOD;
            g[u]=(g[u]*g[v]+g[u]+g[v])%MOD;
        }
    }
    g[u]++;
    f[u]+=(op==1)?u:1;
    f[u]%=MOD;
}

signed main()
{
    n=read(),op=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    cout<<f[1]<<endl;
    return 0;
}
