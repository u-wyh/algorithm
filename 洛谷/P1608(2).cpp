#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

int n,m;
int dis[MAXN][MAXN];
int d[MAXN];
bool vis[MAXN];
int sum[MAXN];
auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);

void build() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dis[i][j] = INT_MAX;
        }
    }
}

int main()
{
    cin>>n>>m;
    build();
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=min(dis[u][v],w);
    }
    for(int i=1;i<=n;i++){
        d[i]=INT_MAX;
    }
    d[1]=0;
    sum[1]=1;
    heap.push({1,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=1;i<=n;i++){
            if(dis[u][i]!=INT_MAX){
                if(!vis[i]&&d[i]>d[u]+dis[u][i]){
                    d[i]=d[u]+dis[u][i];
                    sum[i]=sum[u];
                    heap.push({i,d[i]});
                }
                else if(!vis[i]&&d[i]==d[u]+dis[u][i]){
                    sum[i]+=sum[u];
                }
            }
        }
    }
    if(d[n]==INT_MAX){
        cout<<"No answer"<<endl;
        return 0;
    }
    cout<<d[n]<<' '<<sum[n]<<endl;
    return 0;
}
