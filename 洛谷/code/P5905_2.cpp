// Johnson全源最短路，C++版
// 一共n个点，m条有向边，边有边权，可能有负边、重边、自环
// 如果图中存在负环，打印-1即可，否则计算任意两点的最短距离
// 如果不存在通路，认为距离是10^9，每个点到自己的距离认为是0
// 无负环时，输出n行结果，点i到点j的最短距离记为dist(i, j)
// 第i行的输出 = 累加所有 { dist(i, j) * j }，1 <= j <= n
// 1 <= n <= 3 * 10^3
// 1 <= m <= 6 * 10^3
// -3 * 10^5 <= 边权 <= +3 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P5905
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e3+5;
const int MAXM = 9e3+5;
const int MAXL = 5e6+5;
const int INF = 1e9;

int n,m;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cntg=1;

// h[i]表示的是从虚拟点到任一点的最小距离
// 从u到v的边权w  会变成 w+h[u]-h[v]
// 这个一定是大于等于0的  因为如果w+h[u]<h[v] 那么spfa就会更新
// 借助于这个 我们可以实现用dijkstra算法求最短路
int h[MAXN];
int update[MAXN];
bool enter[MAXN];
int que[MAXL];

int dis[MAXN];
bool vis[MAXN];

struct node{
    int u,d;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.d>b.d;
    }
};
priority_queue<node,vector<node>,compare>heap;

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

bool spfa(int s){
    for(int i=1;i<=n;i++){
        h[i]=INF;
    }

    h[s]=0;
    update[s]=1;
    enter[s]=true;

    int ql=1,qr=0;
    que[++qr]=s;
    while(ql<=qr){
        int u=que[ql++];
        enter[u]=false;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(h[v]>h[u]+w){
                h[v]=h[u]+w;
                if(!enter[v]){
                    if(++update[v]>n){
                        return true;
                    }
                    que[++qr]=v;
                    enter[v]=true;
                }
            }
        }
    }
    return false;
}

void dijkstra(int s){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        vis[i]=false;
    }
    dis[s]=0;
    heap.push({s,0});
    while(!heap.empty()){
        int u=heap.top().u;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
    }

    int virtualnode=0;
    for(int i=1;i<=n;i++){
        addedge(virtualnode,i,0);
    }
    
    if(spfa(virtualnode)){
        cout<<-1<<endl;
    }
    else{
        for(int u=1;u<=n;u++){
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                int w=weight[i];
                weight[i]=w+h[u]-h[v];
            }
        }
        for(int u=1;u<=n;u++){
            dijkstra(u);
            long long ans=0;
            for(int j=1;j<=n;j++){
                if(dis[j]==INF){
                    ans+=1ll*j*INF;
                }
                else{
                    ans+=1ll*j*(dis[j]-h[u]+h[j]);
                }
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}