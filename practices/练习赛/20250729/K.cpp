#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 2e5+5;
const int LIMIT = 20;
const int MAXM = 1<<22;
const int INF = 1e9;

int n,m,k,p;
int sta[MAXN];
int dep[MAXN];
int st[MAXN][LIMIT];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

int val[MAXN];
int f[MAXN][2];
int g[MAXN][2];

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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        int w=weight[i];
        sta[v]=sta[u]|w;
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int main()
{
    n=read(),m=read(),k=read();
    p=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=0;i<m;i++){
        int t=read();
        weight[2*t]=(1<<i);
        weight[2*t-1]=(1<<i);
    }
    dfs(1,0);
    for(int i=1;i<=k;i++){
        int u,v;
        u=read(),v=read();
        int fa=lca(u,v);
        val[i]=(sta[v]|sta[fa])|(sta[u]^sta[fa]);
    }
    int status=(1<<m)-1;
    for(int i=0;i<=status;i++){
        g[i][0]=INF;//边数
        f[i][0]=0;//方案
    }
    f[0][0]=1,g[0][0]=0;
    for(int i=1;i<=n;i++){
        
    }
    return 0;
}