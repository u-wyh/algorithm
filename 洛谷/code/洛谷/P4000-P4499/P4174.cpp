// https://www.luogu.com.cn/problem/P4174
// 题意：有 N 个中转站可选建，建第 i 个站成本为 P_i；
// 有 M 个用户群，
// 第 i 个用户群需要同时建立 A_i 和 B_i 才能获益 C_i，
// 求最大净获利（总获益减去总建站成本）。
// 数据范围：N <= 5000，M <= 50000，
// 0 <= P_i, C_i <= 100，1 <= A_i, B_i <= N。
// 算法标签：Dinic、最小割、最大权闭合子图
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5005;
const int MAXM = 5e4+5;
const int MAXV = MAXN+MAXM;
const int MAXE = 7*MAXM;
const int INF = 1e15;

int n,m,s,t;

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

signed main()
{
    n=read(),m=read();
    s=n+m+1,t=s+1;
    int all=0;
    for(int i=1;i<=n;i++){
        int val=read();
        addedge(m+i,t,val);
    }
    for(int i=1;i<=m;i++){
        int x1=read();
        int x2=read();
        addedge(i,m+x1,INF);
        addedge(i,m+x2,INF);
        int val=read();
        all+=val;
        addedge(s,i,val);
    }
    int flow=maxflow();
    cout<<(all-flow)<<endl;
    return 0;
}