#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int MAXN = 260000;
const int MAXM = 1200000;

int n,m,k;
int dis[MAXN];
bool vis[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b){
        return a.second>b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dijkstra(){
    for(int i=1;i<=n*m;i++){
        dis[i]=INF;
    }
    dis[1]=0;
    heap.push({1,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=1;
        if(u==n*m){
            break;
        }
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
}


int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='E'){
                if(j!=m)//右
                    addedge(i*m+j,i*m+j+1,0);
                if(i!=0)//上
                    addedge(i*m+j,i*m+j-m,3);
                if(j!=1)//左
                    addedge(i*m+j,i*m+j-1,2);
                if(i!=n-1)//下
                    addedge(i*m+j,i*m+j+m,1);
            }
            else if(c=='W'){
                if(j!=m)//
                    addedge(i*m+j,i*m+j+1,2);
                if(i!=0)//上
                    addedge(i*m+j,i*m+j-m,1);
                if(j!=1)//
                    addedge(i*m+j,i*m+j-1,0);
                if(i!=n-1)//下
                    addedge(i*m+j,i*m+j+m,3);
            }
            else if(c=='N'){
                if(j!=m)//
                    addedge(i*m+j,i*m+j+1,1);
                if(i!=0)//上
                    addedge(i*m+j,i*m+j-m,0);
                if(j!=1)//
                    addedge(i*m+j,i*m+j-1,3);
                if(i!=n-1)//下
                    addedge(i*m+j,i*m+j+m,2);
            }
            else if(c=='S'){
                if(j!=m)//左
                    addedge(i*m+j,i*m+j+1,3);
                if(i!=0)//上
                    addedge(i*m+j,i*m+j-m,2);
                if(j!=1)//右
                    addedge(i*m+j,i*m+j-1,1);
                if(i!=n-1)//下
                    addedge(i*m+j,i*m+j+m,0);
            }
            else{
                if(j!=m)//左
                    addedge(i*m+j,i*m+j+1,INF);
                if(i!=0)//上
                    addedge(i*m+j,i*m+j-m,INF);
                if(j!=1)//右
                    addedge(i*m+j,i*m+j-1,INF);
                if(i!=n-1)//下
                    addedge(i*m+j,i*m+j+m,INF);
            }
        }
    }
    dijkstra();
    if(dis[n*m]==INF){
        dis[n*m]=-1;
    }
    cout<<dis[n*m]<<endl;
    return 0;
}