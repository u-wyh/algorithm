// https://www.luogu.com.cn/problem/P1131
// 题意：给一棵带权树和信号源 S。信号沿边传播，到达节点后立即继续向外传。
// 一次可把一条边的传播时间加 1，
// 求让从 S 出发的信号同时到达所有终止节点的最少操作数。
// 数据范围：1 ≤ N ≤ 500000，1 ≤ t[e] ≤ 10^6。
// 难度评分：1500（洛谷分级换算）
// 算法标签：深度优先搜索、树形动态规划

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
long dis[MAXN];//以i位头结点的子树  向下最深的距离
long ans=0;
int n,st;

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        int w=weight[i];
        if(v==f){
            continue;
        }
        dfs(v,u);
        dis[u]=max(dis[u],dis[v]+w);
    }
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        int w=weight[i];
        if(v==f){
            continue;
        }
        ans+=dis[u]-dis[v]-w;
    }
}

int main()
{
    cin>>n>>st;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs(st,0);
    cout<<ans;
    return 0;
}
