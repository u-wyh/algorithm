//https://www.luogu.com.cn/problem/P3376
//基于bfs的Edmonds–Karp 算法
//每次求增广
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 205;
const int MAXM = 10005;
const int INF = 1e10;

int n,m,s,t;

//这里编号从2开始 为了正反边编号寻找方便
int cnt=2;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];//这个是边的容量  在bfs时会发生变化

//查询回溯时的信息
int fa[MAXN];
int edge[MAXN];

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

//BFS寻找增广路径
bool bfs(){
    for(int i=1;i<=n;i++){
        fa[i]=-1;
    }
    queue<int>q;
    q.push(s);
    fa[s]=-2;//源点标记为已访问  只要不是-1就行

    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(fa[v]==-1&&w>0){
                fa[v]=u;
                edge[v]=i;
                if(v==t){
                    return true;
                }
                q.push(v);
            }
        }
    }
    return false;
}

//Edmonds-Karp算法计算最大流
int maxflow(){
    int flow=0;
    while(bfs()){
        int minflow=INF;
        //从汇点回溯，计算增广路径上的最小剩余容量
        for(int v=t;v!=s;v=fa[v]){
            minflow=min(minflow,weight[edge[v]]);
        }
        //更新残留网络
        for(int v=t;v!=s;v=fa[v]){
            weight[edge[v]]-=minflow;//正向边减流量
            weight[edge[v]^1]+=minflow;//反向边加流量
        }
        flow+=minflow;//累加本次增广的流量
    }
    return flow;
}

signed main()
{
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,0);
    }
    cout<<maxflow()<<endl;
    return 0;
}