// https://www.luogu.com.cn/problem/P5007
// 题意：给定以 1 为根的 n 个节点的树，
// 定义「毒瘤集」为集合中任意两点不存在祖先-后代关系的点集；
// 当 T=0 时每点价值为 1，T=1 时点 i 价值为 i，
// 求所有毒瘤集的价值之和的总和对 100,000,007 取模。
// 数据范围：n <= 10^6，T ∈ {0, 1}。
// 难度评分：1500（洛谷分级换算）
// 算法标签：树形动态规划
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
