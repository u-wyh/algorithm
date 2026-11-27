// https://www.luogu.com.cn/problem/P3412
// 题意：输入一棵树（地下洞穴）的节点数 n，以及 n-1 条树边 (u, v)。
// 在树上等概率随机任选起点 a 和终点 b（允许 a = b），在节点处每次等概率移动到其相邻节点（父节点或任一子节点），走到 b 即停止。
// 求所有 (a, b) 对的随机游走期望步数的平均值，将其表示为既约分数 y/x 后输出 y * x^(-1) mod 998244353。
// 输出一个整数，表示期望步数对 998244353 取模的结果。
// 数据范围：1 <= n <= 100000，模数为 998244353。
#include<bits/stdc++.h>
// 算法标签：树形动态规划、期望、快速幂
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MOD = 998244353;

int n;
int ans;

int sz[MAXN];
int deg[MAXN];
int f[MAXN];
int g[MAXN];
int F[MAXN];
int G[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u,int fa){
    sz[u]=1;
    f[u]=deg[u];
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        sz[u]+=sz[v];
        f[u]=(f[u]+f[v])%MOD;
    }
    // for(int i=head[u];i;i=nxt[i]){
    //     int v=to[i];
    //     if(v!=fa){
    //         g[v]=(g[u]+f[u]-f[v]+MOD)%MOD;
    //     }
    // }
}

void dfs2(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            g[v]=(g[u]+f[u]-f[v])%MOD;
            dfs2(v,u);
            F[v]=(F[v]+(f[v]*sz[v])%MOD)%MOD;
            G[v]=(G[v]+(g[v]*sz[v])%MOD)%MOD;
            ans=(ans+(F[v]*(sz[u]-sz[v])%MOD))%MOD;
            ans=(ans+(G[v]*(sz[u]-sz[v])%MOD))%MOD;
            F[u]=(F[u]+F[v])%MOD;
            G[u]=(G[u]+G[v])%MOD;
        }
    }
}

signed main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        deg[u]++,deg[v]++;
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,0);
    int inv=power(n*n%MOD,MOD-2);
    ans=(ans*inv)%MOD;
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}