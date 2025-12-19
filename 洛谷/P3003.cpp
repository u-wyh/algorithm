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
