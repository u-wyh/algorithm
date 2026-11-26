// https://www.luogu.com.cn/problem/P3020
// 题意：输入谷仓数 N、双向牛道数 M，以及每条牛道连接的谷仓 A_i, B_i 和该路上的奶牛数量 C_i（可能有重边）。
// 从 1 号谷仓走到 N 号谷仓，必须给路上遇到的每头不同奶牛发一份点心（不在乎路径长度）。
// 求从 1 到 N 最少需要携带多少份点心。
// 输出一行一个整数，表示最少点心数量。
// 数据范围：对于 100% 的数据，1 <= N <= 50000，1 <= M <= 50000，0 <= C_i <= 1000。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 4e5+5;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int n,m,st,en1,en2;
int val[MAXN];
int dis[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
bool vis[MAXN];

int main()
{
    cin>>n>>m;
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
    dis[1]=0;
    heap.push({1,0});
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
    cout<<dis[n];
    return 0;
}

