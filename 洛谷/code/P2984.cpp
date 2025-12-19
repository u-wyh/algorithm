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

