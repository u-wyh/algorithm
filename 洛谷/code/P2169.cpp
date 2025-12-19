#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 1e6+5;

int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];
int n,m;
struct node{
    int u,v,w;
}edge[MAXM];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
//初始化建立小根堆
vector<pair<int ,int >>graph[MAXN];
int dis[MAXN];
//记录到源点的最小距离
bool vis[MAXN];
//记录这个点是否被访问过

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=head[x];i;i=Next[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        while(st[top]!=x){
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        edge[i].u=u,edge[i].v=v,edge[i].w=w;
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=m;i++){
        if(col[edge[i].u]!=col[edge[i].v]){
            graph[col[edge[i].u]].push_back({col[edge[i].v],edge[i].w});
        }
    }

    for(int i=1;i<=color;i++){
        dis[i]=INT_MAX;
    }
    heap.push({col[1],0});
    dis[col[1]]=0;
    while(!heap.empty()){
        //cout<<666<<endl;
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        if(u==col[n]){
            break;
        }
        for(int i=0;i<graph[u].size();i++){
            int v=graph[u][i].first;
            int w=graph[u][i].second;
            if(!vis[v]&&(w+dis[u])<dis[v]){
                dis[v]=w+dis[u];
                heap.push({v,dis[u]+w});
            }
        }
    }
    cout<<dis[col[n]]<<endl;
    return 0;
}

