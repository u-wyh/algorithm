#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int INF = 1e9;

int n,m,st,en;

int dis[MAXN][MAXN];
int pos[MAXN][MAXN];//表示从i出发  如果不能直接到达j  下一步到哪
int degree[MAXN];//记录每个节点的度

double dp[MAXN][MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void bfs(int s){
    queue<int>q;//边权只会使1  所以用queue即可
    dis[s][s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(1+dis[s][u]<dis[s][v]){
                dis[s][v]=1+dis[s][u];
                q.push(v);
            }
        }
    }
}

double dfs(int u,int v){
    if(dp[u][v]<INF-1){
        return dp[u][v];
    }

    double res=0;
    int to1=pos[pos[u][v]][v];
    res+=dfs(to1,v);
    for(int i=head[v];i;i=nxt[i]){
        int t=to[i];
        res+=dfs(to1,t);
    }
    res=1+res/(degree[v]+1);
    dp[u][v]=res;
    return res;
}

int main()
{
    cin>>n>>m>>st>>en;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[i][j]=INF;
            dp[i][j]=INF;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        degree[u]++;
        degree[v]++;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        bfs(i);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j){
                dp[i][j]=0;
            }
            else if(dis[i][j]<=2){
                dp[i][j]=1;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(dis[i][j]<2){
                continue;
            }
            int d=INF;
            for(int ei=head[i];ei;ei=nxt[ei]){
                int v=to[ei];
                if(dis[v][j]<d){
                    d=dis[v][j];
                    pos[i][j]=v;
                }
                else if(dis[v][j]==d&&v<pos[i][j]){
                    pos[i][j]=v;
                }
            }
        }
    }

    dfs(st,en);

    printf("%.3lf",dp[st][en]);
    return 0;
}