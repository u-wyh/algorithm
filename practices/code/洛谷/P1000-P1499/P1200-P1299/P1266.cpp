// https://www.luogu.com.cn/problem/P1266
// 题意：给定 N 点（0..N-1）M 条有向边的道路网（无重边），
// 起点 0 初始速度 70，终点 D。
// 题意：每条边有长度 L 与限速 V：若 V > 0，速度瞬间变为 V，
// 耗时 L/V；若 V = 0，沿用前速耗时 L/V_old。
// 题意：求从 0 到 D 用时最快的唯一路径。
// 输入：第一行 N, M, D，
// 接下来 M 行每行输入有向边 A, B, V, L。
// 输出：一行按顺序输出从 0 到 D 经过的路口编号。
// 数据范围：2 <= N <= 150，1 <= M <= 22500，
// 0 <= A, B < N（默认 0 <= D < N）。
// 数据范围：0 <= V <= 500，1 <= L <= 500。
// 难度评分：1800（洛谷分级换算）
// 算法标签：Dijkstra、分层图、最短路
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 155;
const int MAXM = 100005;
const int MAXV = 1005;

int n,m,en,maxv;
double dis[MAXN][MAXV];
bool vis[MAXN][MAXV];

struct node{
    int u,v;
}from[MAXN][MAXV];

int cnt=1;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int v[MAXM];
int len[MAXM];

struct Compare {
    bool operator()(const pair<double, pair<int, int>>& a, const pair<double, pair<int, int>>& b) {
        return a.first > b.first; // 小根堆，按 double 值升序排列
    }
};

priority_queue<pair<double,pair<int, int>>, vector<std::pair<double, std::pair<int, int>>>,Compare> heap;

void addedge(int u,int x,int w,int s){
    Next[cnt]=head[u];
    to[cnt]=x;
    v[cnt]=w;
    len[cnt]=s;
    head[u]=cnt++;
}

void out(int u, int v) {
    if (u == 1) {
        return;
    }
    out(from[u][v].u, from[u][v].v); // 递归调用
    cout << u - 1 << ' ';
}

void dijstra(){
    for(int i=1;i<=n;i++){
        for(int j=0;j<=maxv;j++){
            dis[i][j]=1e9;
        }
    }
    dis[1][70]=0;
    heap.push({0,{1,70}});
    while(!heap.empty()){
        int u=heap.top().second.first;
        int uv=heap.top().second.second;
        //cout<<u<<' '<<uv<<endl;
        heap.pop();
        if(vis[u][uv]){
            continue;
        }
        vis[u][uv]=true;
        for(int i=head[u];i;i=Next[i]){
            int x=to[i];
            int w=v[i];
            int s=len[i];
            if(w){
                if(dis[x][w]>dis[u][uv]+1.0*s/w){
                    dis[x][w]=dis[u][uv]+1.0*s/w;
                    from[x][w]={u,uv};
                    if(!vis[x][w])
                        heap.push({dis[x][w],{x,w}});
                }
            }
            else{
                w=uv;
                if(dis[x][w]>dis[u][uv]+1.0*s/w){
                    dis[x][w]=dis[u][uv]+1.0*s/w;
                    from[x][w]={u,uv};
                    if(!vis[x][w])
                        heap.push({dis[x][w],{x,w}});
                }
            }
        }
    }
    int v=0;
    for(int i=1;i<=maxv;i++){
        if(dis[en][v]>dis[en][i]){
            v=i;
        }
    }
    cout<<0<<' ';
    out(en,v);
    cout<<endl;
}

int main()
{
    cin>>n>>m>>en;
    en++;
    for(int i=1;i<=m;i++){
        int u,v,w,s;
        cin>>u>>v>>w>>s;
        maxv=max(maxv,w);
        u++,v++;
        addedge(u,v,w,s);
    }
    dijstra();
    return 0;
}
