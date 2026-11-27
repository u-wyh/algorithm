// https://www.luogu.com.cn/problem/P3376
// 题意：给一张有向网络，有 n 个点、m 条边，s 是源点，t 是汇点。
// 每条边 (u, v, w) 表示从 u 到 v 最多可以送 w 单位的流量。
// 除 s 和 t 外，每个点的总流入量要等于总流出量。
// 输出从 s 最多能送多少流量到 t。
// 数据范围：1 ≤ n ≤ 200，1 ≤ m ≤ 5000，
// 0 ≤ w < 2^31。
// 算法标签：最大流、Dinic

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 205;
const int MAXM = 1e4+5;
const int INF = 1e10;

int n,m,s,t;

int dep[MAXN];
int iter[MAXN];

int cnt=2;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int now[MAXM];
int cap[MAXM];

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
    for(int i=1;i<=n;i++){
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

int dfs(int u,int f){
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,min(f,w-k));
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

int maxflow(){
    int flow=0;
    while(bfs()){
        for(int i=1;i<=n;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

signed main()
{
    n=read(),m=read(),s=read(),t=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
    }
    cout<<maxflow()<<endl;
    return 0;
}