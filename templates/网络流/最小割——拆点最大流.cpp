// https://www.luogu.com.cn/problem/P1345
// 这道题主要用的是拆点的做法
// 将一个点拆成入点和出点  因为除了s t以外  所有点都可以拆  所以每个点的入点到出点连一个权为1的边
// s t的入点到出点连的是INF
// 连接的无向边变为两条有向边  权为INF  表示不可拆   反边都是0
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 205;//这里是2*n
const int MAXM = 3000;//这里是 2*n+4*m
const int INF = 1e18;

int n,m,s,t;

int dep[MAXN];
int iter[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int now[MAXM];
int cap[MAXM];
int cnt=2;

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    head[u]=cnt++;
}

//BFS构建分层图，并判断是否存在增广路径
bool bfs(){
    for(int i=1;i<=2*n;i++){
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

// DFS寻找增广路径（多路增广）
//多路增广的含义是来到了一个节点 不仅仅是只去一条边增广  而是去多条边一起增广
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

// Dinic算法主函数
int maxflow(){
    int flow=0;
    while(bfs()){
        //当前弧全部初始化为最初值
        for(int i=1;i<=2*n;i++){
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
    cin>>n>>m>>s>>t;
    for(int i=1;i<=n;i++){
        if(i==s||i==t){
            addedge(i,i+n,INF);
            addedge(i+n,i,0);//反边
        }
        else{
            addedge(i,i+n,1);
            addedge(i+n,i,0);//反边
        }
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u+n,v,INF);
        addedge(v,u+n,0);//反边

        addedge(v+n,u,INF);
        addedge(u,v+n,0);//反边
    }
    cout<<maxflow()<<endl;
    return 0;
}