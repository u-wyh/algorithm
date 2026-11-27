// https://www.luogu.com.cn/problem/P4096
// 题意：第一行输入博弈树节点数
// n（1 为根且为黑方决策，相邻层黑白交替，
// 叶节点状态未知；内部节点黑取 OR、白取 AND）。
// 后 n-1 行依次给出节点 2..n 的父节点编号。
// 定义「最小黑/白方胜集合」为使根必胜所需的最小叶节点集合，
// 同时属于某个最小黑方胜集合与某个最小白方胜集合的叶节点称为关键叶节点。
// 输出一行三个整数：
// 编号最小的关键叶节点编号、关键叶节点个数、所有关键叶节点编号的异或和。
// 数据范围：1 <= n <= 2*10^5，
// 且对 i != 1 其父节点编号小于 i。
// 算法标签：树形动态规划、深度优先搜索、博弈论
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int INF = 1e6;

int n;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int dep[MAXN];
int f[MAXN];
int g[MAXN];

bool w[MAXN];
bool b[MAXN];

int ans[MAXN];
int len;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    if(head[u]==0){
        f[u]=g[u]=1;
        return ;
    }
    dep[u]=dep[fa]+1;
    if(dep[u]%2){
        f[u]=INF;
    }
    else{
        g[u]=INF;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
        if(dep[u]%2==1){
            f[u]=min(f[u],f[v]);
            g[u]+=g[v];
        }
        else{
            f[u]+=f[v];
            g[u]=min(g[u],g[v]);
        }
    }
}

void dfs(int u,bool ok1,bool ok2){
    int d=dep[u];
    b[u]=ok1;
    w[u]=ok2;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(d%2){
            if(f[u]==f[v]){
                dfs(v,ok1,ok2);
            }
            else{
                dfs(v,0,ok2);
            }
        }
        else{
            if(g[u]==g[v]){
                dfs(v,ok1,ok2);
            }
            else{
                dfs(v,ok1,0);
            }
        }
    }
}

int main()
{
    cin>>n;
    for(int i=2;i<=n;i++){
        int u;
        cin>>u;
        addedge(u,i);
    }

    dfs(1,0);
    dfs(1,1,1);

    int val=0;
    for(int i=1;i<=n;i++){
        if(head[i]==0&&w[i]&&b[i]){
            ans[++len]=i;
            val^=i;
        }
    }
    cout<<ans[1]<<' '<<len<<' '<<val<<endl;
    return 0;
}