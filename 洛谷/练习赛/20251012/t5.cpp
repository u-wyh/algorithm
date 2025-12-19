#include<bits/stdc++.h>
using namespace std;
const int MAXN = 510;
const int MAXM = 4*MAXN*MAXN;
const int INF = 1e9;

int n,m;
long long c,d;
int s,t;
char str[MAXN][MAXN];

int dep[MAXN];
int iter[MAXN];

int cnt;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cap[MAXM];

int source_edges[MAXN];
int sink_edges[MAXN];

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    head[v]=cnt++;
}

bool bfs(){
    memset(dep,-1,sizeof(dep));
    queue<int>q;
    dep[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i!=-1;i=nxt[i]){
            int v=to[i];
            if(dep[v]<0&&cap[i]>0){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>=0;
}

int dfs(int u,int f){
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        if(dep[u]+1==dep[v]&&cap[i]>0){
            int d=dfs(v,min(f,cap[i]));
            if(d>0){
                cap[i]-=d;      
                cap[i^1]+=d;    
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
        for(int i=0;i<=t;i++) iter[i]=head[i];
        int f;
        while((f=dfs(s,INF))>0){
            flow+=f;
        }
    }
    return flow;
}

int main()
{
    scanf("%d %d %lld %lld",&n,&m,&c,&d);
    s=0,t=n+m+1;
    
    memset(head,-1,sizeof(head));
    cnt=0;
    
    int total_empty=0;
    for(int i=1;i<=n;i++){
        scanf("%s",str[i]+1);
        for(int j=1;j<=m;j++){
            if(str[i][j]=='.'){
                total_empty++;
                addedge(i,j+n,1);
            }
        }
    }
    
    // 记录源点到行节点的边
    for(int i=1;i<=n;i++){
        addedge(s,i,0);
        source_edges[i]=cnt-2;
    }
    
    // 记录列节点到汇点的边
    for(int j=1;j<=m;j++){
        addedge(j+n,t,0);
        sink_edges[j]=cnt-2;
    }
    
    long long ans=d*total_empty;
    int flow=0;
    
    for(int k=1;k<=max(n,m);k++){
        // 增加容量
        for(int i=1;i<=n;i++){
            cap[source_edges[i]]++;
        }
        for(int j=1;j<=m;j++){
            cap[sink_edges[j]]++;
        }
        
        flow+=maxflow();
        long long cost=c*k+d*(total_empty-flow);
        if(cost<ans){
            ans=cost;
        }
    }
    
    cout<<ans<<endl;
    return 0;
}