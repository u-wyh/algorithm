// 用途：有向容量网络最大流；输入 n m s t 和 m 条 u v 容量。
// 时间：一般上界 O(n²m)。
// 空间：O(n+m)。
// 注意：n<=200，m<=5000；同点源汇输出 0。
// 例题：https://www.luogu.com.cn/problem/P3376
// 题意：求容量网络中源点到汇点能送出的最大流量。
// 思路：BFS 建分层图，DFS 沿允许边反复增广。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 205;
const int MAXM = 10005;
const int INF = 1e10;

int n,m,s,t;

int dep[MAXN];//记录深度数组
int iter[MAXN];//当前弧数组 记录这个节点有效访问的第一条边的编号
int que[MAXN];

// 正反边从编号 2 开始配对，反向边编号为 e^1。
int cnt=2;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int now[MAXM];//表示现在的流量
int cap[MAXM];//表示流量限制

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
    // 只沿有剩余容量的边分层，汇点不可达时最大流已求完。
    for(int i=1;i<=n;i++){
        dep[i]=-1;
    }
    int ql=0,qr=0;
    dep[s]=0;
    que[qr++]=s;
    while(ql<qr){
        int u=que[ql++];
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int k=now[i];
            if(dep[v]<0&&(k<w)){
                dep[v]=dep[u]+1;
                que[qr++]=v;
            }
        }
    }
    return dep[t]>=0;// 如果汇点未被访问到，说明无增广路径
}

int dfs(int u,int f){
    // 当前弧沿分层图送出最多 f；增广后同时更新正反残量。
    if(u==t){
        return f;
    }
    int flow=0;
    // 引用当前弧，避免重复扫描已耗尽的边。
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
    cin>>n>>m>>s>>t;
    if(s==t){
        cout<<0<<'\n';
        return 0;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
    }
    cout<<maxflow()<<endl;
    return 0;
}
