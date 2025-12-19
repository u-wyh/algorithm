//P2865  很经典的spfa
//这道题解决的是一个次短路问题  可以走重复边
//这个题目没有松弛操作次数的要求 因为所有边权都是大于0的
//记录松弛次数是为了判断有没有负环
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXM = 2e5+5;

int n,m;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

//spfa需要 这里由于是次短路 
//dis[i][0]表示的是从源点 一般是1或者n节点  到达i节点的最短路径
//dis[i][1]表示的是次短路径
int dis[MAXN][2];
bool vis[MAXN];//表示现在是否在队列中
queue<int>q;//不需要堆  一个队列即可

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void spfa(){
    for(int i=1;i<=n;i++){
        dis[i][0]=1e9;
        dis[i][1]=1e9;
    }
    dis[n][0]=0;
    q.push(n);
    vis[n]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[v][0]>dis[u][0]+w){
                dis[v][1]=dis[v][0];
                dis[v][0]=dis[u][0]+w;
                if(!vis[v]){
                    //不在队列中  才会加入  这里要注意
                    q.push(v);
                    vis[v]=true;
                }
            }
            if(dis[v][1]>dis[u][0]+w&&dis[v][0]<dis[u][0]+w){
                //这里必须要说明是  <  因为如果相等的话是不符合要求的
                dis[v][1]=dis[u][0]+w;
                if(!vis[v]){
                    q.push(v);
                    vis[v]=true;
                }
            }
            if(dis[v][1]>dis[u][1]+w){
                dis[v][1]=dis[u][1]+w;
                if(!vis[v]){
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    spfa();
    cout<<dis[1][1]<<endl;
    return 0;
}