// https://www.luogu.com.cn/problem/P1629
// 题意：邮局在 1，需分别送信到 2 至 n。
// 道路单向并有耗时，每趟只带一件物品，送到后必须返回 1，包括最后一趟。
// 求完成全部往返的最短总时间。
// 数据范围：1 ≤ n ≤ 1000，1 ≤ m ≤ 10^5，
// 端点编号在 [1,n]，1 ≤ w ≤ 10000，任意两点互相可达。
// 算法标签：Dijkstra、反向建图

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXM = 1e6+5;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int n,m;
long long dis[MAXN];
bool vis[MAXN];

auto compare = [](const pair<int, long long >& left, const pair<int, long long >& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, long long>, vector<pair<int, long long >>, decltype(compare)> heap(compare);

int head1[MAXN];
int Next1[MAXM];
int to1[MAXM];
int weight1[MAXM];
int cnt1=1;
priority_queue<pair<int, long long >, vector<pair<int, long long>>, decltype(compare)> heap1(compare);
long long dis1[MAXN];
bool vis1[MAXN];

int main()
{
    cin>>n>>m;
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
        dis[i]=LLONG_MAX;
        dis1[i]=LLONG_MAX;
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
            if(!vis[v]&&(w+dis[u])<dis[v]){
                dis[v]=w+dis[u];
                heap.push({v,dis[u]+w});
            }
        }
    }
    dis1[1]=0;
    heap1.push({1,0});
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
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=dis[i];
        ans+=dis1[i];
    }
    cout<<ans;
    return 0;
}
