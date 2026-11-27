// https://www.luogu.com.cn/problem/P9745
// 题意：给定 n 个点的树，点 i 权值为 x_i。
// 对 n-1 条边共有 2^{n-1} 种删边方案，每种方案权值定义为所有连通块的点权异或和的乘积。
// 求所有 2^{n-1} 种方案的权值之和对 998244353 取模的值。
// 题意：第一行输入 n，第二行输入 x_1..x_n，第三行输入 f_2..f_n（表示 i 与 f_i 有边）；输出一行一个整数。
// 数据范围：1 <= n <= 5 * 10^5，0 <= x_i <= 10^18，1 <= f_i < i。
// 算法标签：树形动态规划、位运算
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 5e5+5;

int n;
long long val[MAXN];

int f[MAXN];
int g[MAXN][64][2];

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

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

void dfs(int u){
    for(int i=0;i<=63;i++){
        g[u][i][(val[u]>>i)&1]=1;
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        for(int i=0;i<=63;i++){
            int t0=g[u][i][0],t1=g[u][i][1];
            g[u][i][0]=(t0*(f[v]+g[v][i][0])+t1*g[v][i][1])%MOD;
            g[u][i][1]=(t0*g[v][i][1]+t1*(f[v]+g[v][i][0]))%MOD;
        }
    }

    for(int i=0;i<=63;i++){
        f[u]=(f[u]+(1LL<<i)%MOD*g[u][i][1]%MOD)%MOD;
    }
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=2;i<=n;i++){
        int u;
        u=read();
        addedge(u,i);
    }
    dfs(1);
    printf("%lld\n",f[1]);
    return 0;
}