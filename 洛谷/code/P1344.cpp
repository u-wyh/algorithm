// https://www.luogu.com.cn/problem/P1344
//这道题要求的是最小割  也就是最大流   除此之外  要求割边尽量少
//这个程序的做法很巧妙  把每条边的边权全部变为原来的10000倍+1
//这种设计确保最小割优先考虑损失最小化，其次考虑卡车数量最小化
//因为只要损失不一样 哪怕有一个的差距  就会被放大为10000   远远大于汽车总数
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 35;
const int MAXM = 2e3+5;
const int BASE = 10000;//这个是为了增加边的容量而设置的
const int INF = 1e18;

int n,m;

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
    for(int i=1;i<=n;i++){
        dep[i]=-1;
    }
    queue<int>q;
    dep[1]=0;
    q.push(1);
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
    return dep[n]>=0;// 如果汇点未被访问到，说明无增广路径
}

// DFS寻找增广路径（多路增广）
//多路增广的含义是来到了一个节点 不仅仅是只去一条边增广  而是去多条边一起增广
int dfs(int u,int f){
    //表示当前来到了u节点 有f的流量可供使用  f就是目前这条路最多可以消耗掉的流量
    if(u==n){
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
        for(int i=1;i<=n;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(1,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w*BASE+1);
        addedge(v,u,0);
    }
    int ans=maxflow();
    cout<<(ans/BASE)<<' '<<(ans%BASE)<<endl;
    return 0;
}