// https://acm.hdu.edu.cn/showproblem.php?pid=3549
// 题意：给 T 组数据，每组给 n 点 m 边的有向图，
// 以及每条边的起点 X、终点 Y 和容量 c。
// 输出：每组按 Case k: 答案 的格式输出
// 从 1 号点到 n 号点的最大流。
// 数据范围：2 <= n <= 15，0 <= m <= 1000，
// 1 <= X, Y <= n，1 <= c <= 1000。
// 算法标签：Edmonds-Karp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20;
const int MAXM = 2005;
const int INF = 1e9;

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

void prepare(){
    for(int i=1;i<=n;i++){
        head[i]=0;
    }
    cnt=2;
}

int main()
{
    int T;
    cin>>T;
    int casenum=0;
    while(T--){
        casenum++;
        cin>>n>>m;
        s=1,t=n;
        prepare();
        for(int i=1;i<=m;i++){
            int u,v,w;
            cin>>u>>v>>w;
            addedge(u,v,w);
            addedge(v,u,0);
        }
        cout<<"Case "<<casenum<<": "<<maxflow()<<endl;
    }
    return 0;
}