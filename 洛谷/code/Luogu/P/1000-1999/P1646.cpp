#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXV = MAXN*MAXN*5;
const int MAXE = 30*MAXV;
const int INF = 1e9;

int n,m,s,t;
int id[MAXN][MAXN];
int nodecnt;

int dep[MAXV];
int iter[MAXV];
int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

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
    n=read(),m=read();
    s=5*m*n-2*n-2*m+1;
    t=s+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            id[i][j]=++nodecnt;
        }
    }
    int all=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int val=read();
            addedge(s,id[i][j],val);
            all+=val;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int val=read();
            addedge(id[i][j],t,val);
            all+=val;
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            int val=read();
            ++nodecnt;
            addedge(s,nodecnt,val);
            addedge(nodecnt,id[i][j],INF);
            addedge(nodecnt,id[i+1][j],INF);
            all+=val;
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            int val=read();
            ++nodecnt;
            addedge(nodecnt,t,val);
            addedge(id[i][j],nodecnt,INF);
            addedge(id[i+1][j],nodecnt,INF);
            all+=val;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++){
            int val=read();
            ++nodecnt;
            addedge(s,nodecnt,val);
            addedge(nodecnt,id[i][j],INF);
            addedge(nodecnt,id[i][j+1],INF);
            all+=val;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++){
            int val=read();
            ++nodecnt;
            addedge(nodecnt,t,val);
            addedge(id[i][j],nodecnt,INF);
            addedge(id[i][j+1],nodecnt,INF);
            all+=val;
        }
    }
    int flow=maxflow();
    cout<<(all-flow)<<endl;
    return 0;
}