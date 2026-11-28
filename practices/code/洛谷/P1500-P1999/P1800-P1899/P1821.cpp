// https://www.luogu.com.cn/problem/P1821
// 题意：给定 n 个农场、m 条有向道路，派对在 x 号农场。
// 每头牛去派对和回家分别走最短路，求所有牛的往返距离中的最大值。
// 数据范围：1 ≤ x ≤ n ≤ 1000，1 ≤ m ≤ 10^5，
// 1 ≤ u,v ≤ n，1 ≤ w ≤ 100，所有农场都与 x 双向可达。
// 难度评分：1300（洛谷分级换算）
// 算法标签：Dijkstra、反图

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1001;
const int MAXM = 100005;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int n,m,x;
int dis[MAXN];
bool vis[MAXN];
auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, long long>, vector<pair<int, long long >>, decltype(compare)> heap(compare);

int head1[MAXN];
int Next1[MAXM];
int to1[MAXM];
int weight1[MAXM];
int cnt1=1;
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap1(compare);
int dis1[MAXN];
bool vis1[MAXN];

int main()
{
    cin>>n>>m>>x;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next1[cnt1]=head1[v];
        to1[cnt1]=u;
        weight1[cnt1]=w;
        head1[v]=cnt1++;
    }
    for(int i=1;i<=n;i++){
        dis[i]=INT_MAX;
        dis1[i]=INT_MAX;
    }
    dis[x]=0;
    heap.push({x,0});
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
            if(!vis[v]&&(w+dis[u])<dis[v]){
                dis[v]=w+dis[u];
                heap.push({v,dis[u]+w});
            }
        }
    }
    dis1[x]=0;
    heap1.push({x,0});
    while(!heap1.empty()){
        int u=heap1.top().first;
        heap1.pop();
        if(vis1[u]){
            continue;
        }
        vis1[u]=true;
        for(int i=head1[u];i>0;i=Next1[i]){
            int v=to1[i];
            int w=weight1[i];
            if(!vis1[v]&&(w+dis1[u])<dis1[v]){
                dis1[v]=w+dis1[u];
                heap1.push({v,dis1[u]+w});
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,dis[i]+dis1[i]);
    }
    cout<<ans;
    return 0;
}
