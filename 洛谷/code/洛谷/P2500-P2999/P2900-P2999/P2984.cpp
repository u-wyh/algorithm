// https://www.luogu.com.cn/problem/P2984
// 题意：输入农场数 N、双向边数 M、询问奶牛数 B，M 条双向边
// (R_i, S_i, L_i)，以及 B 组询问 (P_i, Q_i)。
// 对每组询问，位于 P_i 的奶牛必须先前往 1 号农场取礼物，
// 然后再送到位于 Q_i 的另一头奶牛处。
// 求出每组询问中奶牛需要行走的最短总路程。
// 输出共 B 行，每行一个整数表示对应询问的最短总路程。
// 数据范围：对于 100% 的数据，
// 1 <= B <= 25000，2*B <= N <= 50000，
// N - 1 <= M <= 100000
// 1 <= L_i <= 2000，
// 1 <= R_i, S_i, P_i, Q_i <= N。
// 算法标签：最短路、Dijkstra、优先队列
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
const int MAXM = 200005;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int n,m,t;
int dis[MAXN];
bool vis[MAXN];

int main()
{
    cin>>n>>m>>t;
    for(int i=1;i<=m;i++){
        int u,v,w;
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
    for(int i=0;i<=n;i++){
        dis[i]=INT_MAX;
    }
    dis[1]=0;
    heap.push({1,0});
    while(!heap.empty()){
        int cur=heap.top().first;
        int cost=heap.top().second;
        heap.pop();
        if(vis[cur]){
            continue;
        }
        vis[cur]=true;
        for(int i=head[cur];i>0;i=Next[i]){
            if(!vis[to[i]]&&dis[cur]+weight[i]<dis[to[i]]){
                dis[to[i]]=dis[cur]+weight[i];
                heap.push({to[i],dis[to[i]]});
            }
        }
    }
    for(int i=1;i<=t;i++){
        int a,b;
        cin>>a>>b;
        cout<<dis[a]+dis[b]<<endl;
    }
    return 0;
}

