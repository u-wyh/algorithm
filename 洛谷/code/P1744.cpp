#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101;
const int MAXM = 2001;

auto compare = [](const pair<int, double>& left, const pair<int, double>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, double>, vector<pair<int, double>>, decltype(compare)> heap(compare);
struct node{
    int x,y;
}nums[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
double weight[MAXM];
double dis[MAXN];
bool vis[MAXN];
int cnt=1;
int n,m,st,en;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        double w;
        cin>>u>>v;
        w=sqrt(pow(abs(nums[u].x-nums[v].x),2)+pow(abs(nums[u].y-nums[v].y),2));
        //cout<<w;
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
        dis[i]=1e9;
    }
    cin>>st>>en;
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
            double w=weight[i];
            if(!vis[v]&&(w+dis[u])<dis[v]){
                dis[v]=w+dis[u];
                heap.push({v,dis[u]+w});
            }
        }
    }
    printf("%.2lf",dis[en]);
    return 0;
}

