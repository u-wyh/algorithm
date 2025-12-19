// https://loj.ac/p/115
// 这道题是没有源点、汇点  每条边的流量有一个上下界   查询是否存在可行流
// 这道题的做法是根据每条边的下界处理好in数组  即每个节点净流入量
// 我们根据每条边的上界建图  虚建源点和汇点
// 如果净流量大于0  那么源点向这个点流入流量  否则向虚点流出流量
// 然后跑最大流  存在可行流的条件是最大流是源点流出的流量之和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 10205;
const int MAXV = 205;
const int MAXE = MAXM*2+MAXN*2;
const int INF = 1e9;

int n,m,s,t;
int in[MAXN];

struct Edge{
    int u,v,lower,higher;
};
Edge edge[MAXM];
int edgeid[MAXM];

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
    s=n+1,t=s+1;
    for(int i=1;i<=m;i++){
        edge[i].u=read(),edge[i].v=read(),edge[i].lower=read(),edge[i].higher=read();
    }
    for(int i=1;i<=m;i++){
        int u=edge[i].u;
        int v=edge[i].v;
        int lower=edge[i].lower;
        int higher=edge[i].higher;
        edgeid[i]=cnt;

        addedge(u,v,higher-lower);

        in[u]-=lower;
        in[v]+=lower;
    }

    // 添加附加源汇的边  并记录附加边总权值
    int need=0;
    for(int i=1;i<=n;i++){
        if(in[i]>0){
            addedge(s,i,in[i]);
            need+=in[i];
        }
        else{
            addedge(i,t,-in[i]);
        }
    }

    int flow=maxflow();

    if(flow!=need){
        cout<<"NO"<<endl;
    }
    else{
        cout<<"YES"<<endl;
        for(int i=1;i<=m;i++){
            int actual=now[edgeid[i]]+edge[i].lower;
            cout<<actual<<endl;
        }
    }
    return 0;
}