#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int MAXN = 505;
const int MAXV = MAXN*MAXN;
const int MAXE = 16*MAXV;

int n;
int s,t;

int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int weight[MAXE];
int cntg=1;

int dis[MAXV];
bool vis[MAXV];

void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

int getid(int r,int c){
    return r*n+c;
}

int getdown(int r,int c){
    return (r==n)?s:getid(r,c);
}

int getup(int r,int c){
    return (r==0)?t:getid(r-1,c);
}

int getleft(int r,int c){
    return (c==0)?s:getid(r,c-1);
}

int getright(int r,int c){
    return (c==n)?t:getid(r,c);
}

int dijkstra(){
    for(int i=0;i<=t;i++){
        dis[i]=INF;
    }
    dis[s]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap;
    heap.push({0,s});

    while(!heap.empty()){
        int u=heap.top().second;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                heap.push({dis[v],v});
            }
        }
    }
    return dis[t];
}

signed main()
{
    cin>>n;
    s=n*n,t=s+1;

    for(int r=0;r<=n;r++){
        for(int c=0;c<n;c++){
            int w;
            cin>>w;
            addedge(getdown(r,c),getup(r,c),w);
        }
    }
    for(int r=0;r<n;r++){
        for(int c=0;c<=n;c++){
            int w;
            cin>>w;
            addedge(getleft(r,c),getright(r,c),w);
        }
    }
    for(int r=0;r<=n;r++){
        for(int c=0;c<n;c++){
            int w;
            cin>>w;
            addedge(getup(r,c),getdown(r,c),w);
        }
    }
    for(int r=0;r<n;r++){
        for(int c=0;c<=n;c++){
            int w;
            cin>>w;
            addedge(getright(r,c),getleft(r,c),w);
        }
    }

    cout<<dijkstra()<<endl;
    return 0;
}