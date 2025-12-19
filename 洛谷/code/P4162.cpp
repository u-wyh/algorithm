#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000;
const int MAXM = 10000;

double ans=-100;

int n,m,t;
char s[33][33];
int pos[MAXN];
double dis[MAXN][MAXN];
int cost[MAXN];
bool vis[MAXN];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

inline int id(int x,int y){
    return m*(x-1)+y;
}

inline void addedge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void spfa(int st){
    for(int i=1;i<=n*m;i++){
        cost[i]=1000,vis[i]=false;
    }
    cost[st]=pos[st];
    vis[st]=1;
    queue<int>q;
    q.push(st);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        ans=max(ans,dis[st][u]);
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(cost[v]>cost[u]+w){
                cost[v]=cost[u]+w;
                if(cost[v]<=t&&!vis[v]){
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int u=1;u<=n;u++){
                for(int v=1;v<=m;v++){
                    dis[id(i,j)][id(u,v)]=sqrt(pow((i-u),2)+pow((j-v),2));
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]=='1'){
                pos[id(i,j)]=1;
            }
            for(int k=0;k<4;k++){
                int x=i+walk[k][0],y=j+walk[k][1];
                if(x<=0||x>n||y<=0||y>m){
                    continue;
                }
                addedge(id(i,j),id(x,y),s[x][y]-'0');
            }
        }
    }
    for(int i=1;i<=n*m;i++){
        spfa(i);
    }
    printf("%.6lf",ans);
    return 0;
}