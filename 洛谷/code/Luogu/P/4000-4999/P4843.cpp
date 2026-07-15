#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXV = MAXN+10;
const int MAXE = MAXN*MAXN*2;
const int INF = 1e9;

int n,m,s,t;
int ss,tt;// 附加源点、汇点

int dep[MAXV];
int iter[MAXV];

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];
int ts_id; // 记录t->s边的编号

// 每个节点的下界净流量
int in[MAXV];

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

bool bfs(int s,int t){
    for(int i=1;i<=tt;i++){
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
    return dep[t]>=0;
}

int dfs(int u,int t,int f){
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,t,min(f,w-k));
            if(d>0){
                now[i]+=d;
                now[i^1]-=d;
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

int maxflow(int s,int t){
    int flow=0;
    while(bfs(s,t)){
        for(int i=1;i<=tt;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,t,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

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

int main()
{
    n=read();
    s=n+1,t=s+1,ss=t+1,tt=ss+1;
    for(int i=1;i<=n;i++){
        int m=read();
        for(int j=1;j<=m;j++){
            int u=read();
            addedge(i,u,INF);
            in[i]--;
            in[u]++;
        }
    }
    for(int i=1;i<=n;i++){
        addedge(s,i,INF);
    }
    for(int i=1;i<=n;i++){
        addedge(i,t,INF);
    }
    ts_id=cnt;
    addedge(t,s,INF);   

    for(int i=1;i<=t;i++){
        if(in[i]>0){
            addedge(ss,i,in[i]);
        }
        else if(in[i]<0){
            addedge(i,tt,-in[i]);
        }
    }

    int flow=maxflow(ss,tt);
    int f0=now[ts_id];

    cap[ts_id] = 0;
    cap[ts_id ^ 1] = 0;
    now[ts_id] = 0;
    now[ts_id ^ 1] = 0;

    // 如果求的是最小流 那么就是跑一下退流  用可行流减去退流即可
    // 在残余网络上从t到s跑最大流（退流）
    int flow_back = maxflow(t, s);
            
    // 最小流 = 可行流 - 退流
    printf("%d", f0 - flow_back);
         
    return 0;
}