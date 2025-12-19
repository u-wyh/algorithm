#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30;
const int MAXK = 1005;
const int MAXM = 40005;
const int INF = 1e9;

int n,s,t;
int win[MAXN],lost[MAXN];
int val[MAXN][MAXN];

int nodecnt;
int dep[MAXK];//记录深度数组
int iter[MAXK];//当前弧数组 记录这个节点有效访问的第一条边的编号

int cnt=2;
int head[MAXK];
int nxt[MAXM];
int to[MAXM];
int now[MAXM];//表示现在的流量
int cap[MAXM];//表示流量限制

int teamnode[MAXN];
int gamenode[MAXN][MAXN];

void init(){
    memset(head,0,sizeof(head));
    memset(iter,0,sizeof(iter));
    memset(now,0,sizeof(now)); // 初始化当前流量为0
    cnt=2;
}

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

//BFS构建分层图，并判断是否存在增广路径
bool bfs(){
    for(int i=1;i<=nodecnt;i++){
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
        for(int i=1;i<=nodecnt;i++){
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
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d %d",&win[i],&lost[i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&val[i][j]);
        }
    }

    for(int i=1;i<=n;i++){
        int maxval=win[i];
        for(int j=1;j<=n;j++){
            maxval+=val[i][j];
        }
        bool possible=true;
        for(int k=1;k<=n;k++){
            if(win[k]>maxval){
                possible=false;
                break;
            }
        }
        if(!possible){
            continue;
        }
        init();

        nodecnt=0;
        s=++nodecnt;
        t=++nodecnt;
        for(int j=1;j<=n;j++){
            if(j!=i){
                teamnode[j]=++nodecnt;
            }
        }
        for(int j=1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                gamenode[j][k]=0;
            }
        }
        for(int j=1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                if(j!=i&&k!=i&&val[j][k]>0){
                    gamenode[j][k]=++nodecnt;
                }
            }
        }
        for(int j=1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                if(gamenode[j][k]>0){
                    addedge(s,gamenode[j][k],val[j][k]);
                }
            }
        }
        for(int j=1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                if(gamenode[j][k]>0){
                    addedge(gamenode[j][k],teamnode[j],INF);
                    addedge(gamenode[j][k],teamnode[k],INF);
                }
            }
        }
        for(int j=1;j<=n;j++){
            if(j!=i){
                addedge(teamnode[j],t,maxval-win[j]);
            }
        }

        int total=0;
        for(int j=1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                if(j!=i&&k!=i){
                    total+=val[j][k];
                }
            }
        }
        int flow=maxflow();
        if(flow==total){
            cout<<i<<' ';
        }
    }
    return 0;
}