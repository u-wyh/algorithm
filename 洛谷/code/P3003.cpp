// https://www.luogu.com.cn/problem/P3003
// 题意：输入无向连通图边数 C、牧场数 P、起点 PB、两个终点 PA_1 与 PA_2，以及 C 条双向牛道 (P1_i, P2_i, D_i)。
// 奶牛从牧场 PB 出发，按任意先后顺序访问牧场 PA_1 和 PA_2 送完两个苹果。
// 求她必须行走的最小总距离。
// 输出一行一个整数，表示最短总距离。
// 数据范围：对于 100% 的数据，1 <= C <= 2*10^5，1 <= P <= 10^5
// 1 <= P1_i, P2_i, PB, PA_1, PA_2 <= P，所有边权 D_i 总和不超过 2*10^9。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 4e5+5;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap1(compare);
int n,m,st,en1,en2;
int val[MAXN];
int dis[MAXN];
int dis1[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
bool vis[MAXN];
bool vis1[MAXN];

int main()
{
    cin>>m>>n>>st>>en1>>en2;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    for(int i=1;i<=n;i++){
        dis[i]=INT_MAX;
    }
    dis[st]=0;
    heap.push({st,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(!vis[v]&&dis[u]<dis[v]-w){
                dis[v]=w+dis[u];
                heap.push({v,dis[v]});
            }
        }
    }
    for(int i=1;i<=n;i++){
        dis1[i]=INT_MAX;
    }
    dis1[en1]=0;
    heap1.push({en1,0});
    while(!heap1.empty()){
        int u=heap1.top().first;
        heap1.pop();
        if(vis1[u]){
            continue;
        }
        vis1[u]=true;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(!vis1[v]&&dis1[u]<dis1[v]-w){
                dis1[v]=w+dis1[u];
                heap1.push({v,dis1[v]});
            }
        }
    }
    cout<<min(dis[en1],dis[en2])+dis1[en2];
    return 0;
}
