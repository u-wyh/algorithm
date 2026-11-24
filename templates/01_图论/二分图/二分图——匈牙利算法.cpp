// https://www.luogu.com.cn/problem/P3386
//这是匈牙利算法求最大匹配   具体的方法是通过求增广路径
//找到一个增广路径  那么答案就加一 
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = 5e4+5;

int n,m,e;

bool vis[MAXN];//标记在这一轮中右部节点是否被访问过
int match[MAXN];//记录右部节点的匹配对象（左部节点编号）

//只记录从左边到右边的路径
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

// DFS寻找增广路径   其实就是为u找到一个匹配
bool dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(vis[v]){
            continue;
        }
        // 标记v为已访问    这样的话接下来的点就不会访问他
        vis[v]=true;
        // 如果v未被匹配，或者已匹配但原来的匹配点可以找到新匹配
        if(match[v]==0||dfs(match[v])){
            match[v]=u;
            return true;
        }
    }
    return false;
}

int main()
{
    cin>>n>>m>>e;
    for(int i=1;i<=e;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
    }
    int ans=0;
    for(int u=1;u<=n;u++){
        // 重置访问标记
        for(int i=1;i<=m;i++){
            vis[i]=false;
        }
        if(dfs(u)){
            ans++;// 找到匹配则计数
        }
    }
    cout<<ans<<endl;
    return 0;
}