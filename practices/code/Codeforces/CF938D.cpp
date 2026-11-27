// https://codeforces.com/problemset/problem/938/D
// 题意：n 座城市 m 条双向收费路（权值 w_i），每座城市门票价 a_i。
// 规则：从 i 出发到任意城市 j 买票再返回 i，
// 总花费为 2*dist(i, j) + a_j，可以在原地买票。
// 输出：对每个城市 i = 1..n 输出最小总花费。
// 数据范围：2 <= n <= 2*10^5，1 <= m <= 2*10^5，
// 1 <= w_i, a_i <= 10^{12}。
// 道路不连自己，同一对城市之间至多有一条路。
// 算法标签：多源 Dijkstra
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXM = 2e5+5;

int n,m;

bool vis[MAXN];
int dis[MAXN];

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];
int cnt=1;

struct node{
    int u,dis;
};

struct compare{
    bool operator()(const node&a,const node&b){
        return a.dis>b.dis;
    }
};
priority_queue<node,vector<node>,compare>heap;

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dijkstra(){
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
            if(dis[v]>dis[u]+2*w){
                dis[v]=dis[u]+2*w;
                heap.push({v,dis[v]});
            }
        }
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    for(int i=1;i<=n;i++){
        dis[i]=read();
        heap.push({i,dis[i]});
    }
    dijkstra();
    for(int i=1;i<=n;i++){
        printf("%lld ",dis[i]);
    }
    return 0;
}