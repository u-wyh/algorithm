#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXV = MAXN*MAXN;
const int MAXE = 8*MAXV;
const int INF = 1e9;

int n,s,t;

int val[MAXN][MAXN];
int cost[MAXN];

int dep[MAXV];
int iter[MAXV];

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    now[cnt]=0;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    now[cnt]=0;
    head[v]=cnt++;
}

bool bfs(){
    for(int i=1;i<=t;i++){
        dep[i]=-1;
    }
    queue<int>q;
    dep[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int k=now[i];
            if(dep[v]<0&&(k<w)){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>=0;// 如果汇点未被访问到，说明无增广路径
}

int dfs(int u,int f){
    //表示当前来到了u节点 有f的流量可供使用  f就是目前这条路最多可以消耗掉的流量
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        //注意这里是引用  iter会随着i发生变化
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,min(f,w-k));
            if(d>0){
                now[i]+=d;
                now[i^1]-=d;//更新反向边
                flow+=d;
                f-=d;
                if(f==0){
                    break;
                }
            }
        }
    }
    return flow;
}

int maxflow(){
    int flow=0;
    while(bfs()){
        //当前弧全部初始化为最初值
        for(int i=1;i<=t;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

int main()
{
    cin>>n;
    s=n*n+n+1;
    t=s+1;
    int all=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>val[i][j];
            all+=val[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        cin>>cost[i];
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int node=(i-1)*n+j;
            addedge(s,node,val[i][j]);
            addedge(node,n*n+i,INF);
            addedge(node,n*n+j,INF);
        }
    }
    for(int i=1;i<=n;i++){
        addedge(n*n+i,t,cost[i]);
    }
    int flow=maxflow();
    cout<<(all-flow)<<endl;
    return 0;
}