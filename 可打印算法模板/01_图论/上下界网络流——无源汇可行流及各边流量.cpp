// 用途：判断无源汇的有向网络是否存在满足每条边上下界的循环流，并输出各边流量。
// 时间：一次 Dinic，最坏 O(n²m)。
// 空间：O(n+m)。
// 注意：0≤下界≤上界；所有顶点须满足流入量=流出量；原边流量=下界+残量网络流量。
// 例题：https://loj.ac/p/115
// 题意：每条边有流量范围，求是否存在可行循环流；有则按输入顺序输出每条边的流量。
// 思路：先固定下界，用超级源汇补齐各点流量差；附加源边全部满流即有解。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 10205;
const int MAXV = 205;
const int MAXE = MAXM*2+MAXN*2;
const long long INF = LLONG_MAX / 4;

int n,m,s,t;
long long in[MAXN];

struct Edge{
    int u,v;
    long long lower,higher;
};
Edge edge[MAXM];
int edgeid[MAXM];

int dep[MAXV];
int iter[MAXV];

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
long long now[MAXE];
long long cap[MAXE];

inline long long read(){
    long long x=0,f=1;
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

void addedge(int u,int v,long long w){
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
            long long w=cap[i];
            long long k=now[i];
            if(dep[v]<0&&(k<w)){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>=0;
}

long long dfs(int u,long long f){
    if(u==t){
        return f;
    }
    long long flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        long long w=cap[i];
        long long k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            long long d=dfs(v,min(f,w-k));
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

long long maxflow(){
    long long flow=0;
    while(bfs()){
        for(int i=1;i<=t;i++){
            iter[i]=head[i];
        }
        long long pushed;
        while((pushed=dfs(s,INF))>0){
            flow+=pushed;
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
        long long lower=edge[i].lower;
        long long higher=edge[i].higher;
        edgeid[i]=cnt;

        addedge(u,v,higher-lower);

        in[u]-=lower;
        in[v]+=lower;
    }

    // 添加附加源汇的边  并记录附加边总权值
    long long need=0;
    for(int i=1;i<=n;i++){
        if(in[i]>0){
            addedge(s,i,in[i]);
            need+=in[i];
        }
        else{
            addedge(i,t,-in[i]);
        }
    }

    long long flow=maxflow();

    if(flow!=need){
        cout<<"NO"<<endl;
    }
    else{
        cout<<"YES"<<endl;
        for(int i=1;i<=m;i++){
            long long actual=now[edgeid[i]]+edge[i].lower;
            cout<<actual<<endl;
        }
    }
    return 0;
}
