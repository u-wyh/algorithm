#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101;
const int MAXM = 10001;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int n,m,h,st,en;
int dis[MAXN][MAXN];
bool check[MAXN][MAXN];
int Dis[MAXN];
bool vis[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[i][j]=INT_MAX;
        }
    }
    for(int i=1;i<=n;i++){
        Dis[i]=INT_MAX;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=w;
        dis[v][u]=w;
    }
    cin>>h;
    for(int i=1;i<=h;i++){
        int a,b;
        cin>>a>>b;
        check[a][b]=true;
        check[b][a]=true;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(dis[i][j]!=INT_MAX&&!check[i][j]){
                dis[i][j]=0;
            }
        }
    }
    cin>>st>>en;
    Dis[st]=0;
    heap.push({st,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=1;i<=n;i++){
            if(dis[i][u]!=INT_MAX){
                if(!vis[i]&&Dis[i]>Dis[u]+dis[i][u]){
                    Dis[i]=dis[i][u]+Dis[u];
                    heap.push({i,Dis[i]});
                }
            }
        }
    }
    cout<<Dis[en];
    return 0;
}
