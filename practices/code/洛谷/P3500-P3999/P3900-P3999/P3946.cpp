// https://www.luogu.com.cn/problem/P3946
// 题意：n 个地点、m 条无向边（边长 w_i），走路速度 1 m/s。
// 初始时刻地点 i 积雪高度为 h_i，每秒钟积雪增加 q 毫米。
// 若到达地点 i（不含起点 s 和终点 t）时当地积雪高度 > l_i 则会被困。
// 求在 g 秒内从 s 走到 t 的最短用时，若超时或被困则输出指定字符串。
// 数据范围：n <= 100000，m <= 500000，
// 1 <= s, t <= n，0 <= g, q <= 10^9
// 0 <= w_i <= l_i <= 10^9。
// 难度评分：1800（洛谷分级换算）
// 算法标签：最短路、Dijkstra
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;

int n,m,k,t;
int st,en;

int limit[MAXN];
int dis[MAXN];
bool vis[MAXN];

int cnt = 1;
int head[MAXM];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> heap;

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

inline void addedge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dijkstra(int st) {
    for (int i = 1; i <= n ; i++) {
        dis[i] = INT_MAX;
    }
    dis[st] = 0;
    heap.push({st, 0});
    while (!heap.empty()) {
        int u = heap.top().first;
        heap.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        if(dis[u]>=limit[u]&&u!=t){
            continue;
        }
        if(u==en){
            break;
        }
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int w = weight[i];
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                heap.push({v, dis[v]});
            }
        }
    }
}

int main()
{
    n=read(),m=read(),st=read(),en=read();
    t=read(),k=read();
    for(int i=1;i<=n;i++){
        int u,v;
        u=read(),v=read();
        if(k)
            limit[i]=(v-u+k-1)/k;
        else
            limit[i]=INT_MAX;
    }
    // for(int i=1;i<=n;i++){
    //     cout<<limit[i]<<' ';
    // }
    // cout<<endl;
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dijkstra(st);
    if(dis[en]>t){
        cout<<"wtnap wa kotori no oyatsu desu!";
    }
    else{
        cout<<dis[en]<<endl;
    }
    return 0;
}