// https://www.luogu.com.cn/problem/P9584
// 题意：给定 n 点 n-1 边的树，第 i 条边费用为 c_i，cost(x, y) 为树上简单路径边权和（cost(x, x) = 0）。
// 新增点 n+1，q 次独立询问：若在 k_i 与 n+1 间连一条费用为 w_i 的双向边
// 求 sum_{i=1}^{n+1} sum_{j=1}^{n+1} cost(i, j) 对 998244353 取模的值。
// 题意：第一行输入 n, q，后 n-1 行输入 (u_i, v_i, c_i)，后 q 行输入 (k_i, w_i)；输出 q 行结果。
// 数据范围：2 <= n <= 2 * 10^5，1 <= q <= 2 * 10^5，1 <= u_i, v_i, k_i <= n
// 1 <= c_i, w_i <= 10^6。
// 算法标签：树形动态规划、换根
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 2e5+5;

int n,m;

int val[MAXN];
int sz[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int weight[MAXN<<1];
int to[MAXN<<1];

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs1(int u,int f){
    sz[u]=1;
    val[u]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v==f){
            continue;
        }
        dfs1(v,u);
        sz[u]+=sz[v];
        val[u]+=sz[v]*w+val[v];
    }
    val[u]%=MOD;
}

void dfs2(int u,int f,int w){
    if(f!=0){
        val[u]=val[f]-sz[u]*w+w*(n-sz[u]);
        val[u]%=MOD;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int wi=weight[i];
        if(v==f){
            continue;
        }
        dfs2(v,u,wi);
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs1(1,0);
    dfs2(1,0,0);
    int ans=0;
    for(int i=1;i<=n;i++){
        // cout<<' '<<i<<' '<<val[i]<<endl;
        ans+=val[i];
        ans%=MOD;
    }
    for(int i=1;i<=m;i++){
        int u,w;
        u=read(),w=read();
        int res=ans+2*n*w+2*val[u];
        res=(res%MOD+MOD)%MOD;
        printf("%lld\n",res);
    }
    return 0;
}