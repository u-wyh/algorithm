//P1491
//这道题目要求的是次短路路径的长度 并且不允许经过相同的边  即使这样可能会更近
//如果有多条最短路 那么直接输出最短路即可
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 20005;

int n,m;
struct node{
    int x,y;
}nums[MAXN];
double dis[MAXN];
bool vis[MAXN];
//pre[i]记录这个节点前面的节点是哪个  即是由那个节点转移的
int pre[MAXN];

int cnt=1;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
double weight[MAXM];

struct Compare {
    bool operator()(const std::pair<double, int>& a, const std::pair<double, int>& b) {
        return a.first > b.first; // 小根堆，按 double 值升序排列
    }
};
priority_queue<std::pair<double, int>, vector<std::pair<double, int>>, Compare> heap;

void addedge(int u,int v,double w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dijkstra(int x,int y){
    //表示连接这两个点的边在这次dj中不能用
    for(int i=1;i<=n;i++){
        dis[i]=1e9;
        vis[i]=0;
    }
    dis[1]=0;
    heap.push({0,1});
    while(!heap.empty()){
        int u=heap.top().second;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=Next[i]){
            int v=to[i];
            double w=weight[i];
            if((u==x&&y==v)||(u==y&&v==x)){
                continue;
            }
            if(!vis[v]&&w+dis[u]<dis[v]){
                dis[v]=w+dis[u];
                heap.push({dis[v],v});
                if(x==0&&y==0){
                    //只有在第一次跑最短路的时候 记录当前节点前面转移的节点
                    pre[v]=u;
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        double w=sqrt(pow(abs(nums[u].x-nums[v].x),2)+pow(abs(nums[u].y-nums[v].y),2));
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dijkstra(0,0);//求出其中一条最短路即可 并完成pre数组 
    double ans=1e9;
    for(int i=n;i!=1;i=pre[i]){
        //枚举最短路上所有的边 
        //同时如果有多条最短路 那么限制一条边后  也一定会有一个一样的答案
        dijkstra(pre[i],i);
        ans=min(ans,dis[n]);
    }
    if(ans>=1e9){
        cout<<-1<<endl;
    }
    else{
        printf("%.2lf",ans);
    }
    return 0;
}
