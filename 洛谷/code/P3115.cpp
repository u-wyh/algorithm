// https://www.luogu.com.cn/problem/P3115
// 题意：输入起点城市 A、终点城市 B、航线数 n，以及每条单向航线的固定票价 cost 和依次经过的城市序列。
// 搭乘一条航线可从其中任意一站上车、之后的任意一站下车，不论坐几段都要付全额票价 cost（可重复坐同一航线，每次都付钱）。
// 求从 A 到 B 的最小总花费，以及在花费最小的前提下最少经过多少段航线；无法到达输出 -1 -1。
// 输出两个整数，分别为最小花费和最小航段数。
// 数据范围：1 <= n <= 1000，1 <= cost <= 10^9，1 <= len <= 100，城市编号不超过 1000（花费需用 64 位整数）。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005, MAXM = 4950005; //最多点数，最多边数
const long long INF = 4557430888798830399; //初始化一个极大值，这里要用long long

int st, fi, n, idx; //起点，终点，点的数量，边的数量 
long long dis[MAXN][2], head[MAXN]; //dis[i][0]为起点到点i最少费用，dis[i][1]为最少费用下的最短路径 
struct Edge{int nxt, to, w, c;}edge[MAXM]; //下一条边，到达的点，费用，路径长度 
struct Node{long long x, w;}; //编号，最少花费 
bool operator < (const Node &a, const Node &b) {return a.w > b.w;} //从小到大排序 
bool vis[MAXN];
priority_queue <Node> q;

void add (int from, int to, int w, int c) //建边 
{
    edge[++idx].nxt = head[from];edge[idx].to = to;edge[idx].w = w;edge[idx].c = c;
    head[from] = idx;
}

void init ()
{
    memset (head, -1, sizeof (head));
    memset (dis, 0x3f, sizeof (dis));
    scanf ("%d%d%d", &st, &fi, &n);
    for (int i = 1; i <= n; i++)
    {
        int k, w;
        long long v[105];
        scanf ("%d%d", &w, &k);
        for (int j = 1; j <= k; j++)    scanf ("%lld", &v[j]);
        //从前至后建边 
        for (int x = 1; x <= k; x++)
        for (int y = x + 1; y <= k; y++)    add (v[x], v[y], w, y - x); //建一条连接v[x]、v[y]费用为w路径长为y - x的边 
    }
}

//堆优化dijkstra
void dijkstar (int s)
{
    dis[s][0] = dis[s][1] = 0;
    q.push (Node {s, 0});
    while (!q.empty ())
    {
        Node cur = q.top ();
        q.pop ();
        if (vis[cur.x]) continue;
        vis[cur.x] = 1;
        for (int i = head[cur.x]; i != -1; i = edge[i].nxt)
        {
            int to = edge[i].to;
            if (dis[to][0] > dis[cur.x][0] + edge[i].w) //若有更小的花费，则更新 
            {
                dis[to][0] = dis[cur.x][0] + edge[i].w;
                dis[to][1] = dis[cur.x][1] + edge[i].c;
                if (vis[to])    continue;
                q.push (Node {to, dis[to][0]}); //入队是入编号和花费 
            }
            if (dis[to][0] == dis[cur.x][0] + edge[i].w) //记得特判费用等于的情况 
            {
                dis[to][1] = min (dis[to][1], dis[cur.x][1] + edge[i].c);//费用等于取路径长度小的 
                if (vis[to])    continue;
                q.push (Node {to, dis[to][0]});
            }
        }
    }
}

void output ()
{
    if (dis[fi][0] == INF)  printf ("-1 -1"); //不能到达 
    else                    printf ("%lld %lld", dis[fi][0], dis[fi][1]);
}

int main ()
{
    init ();        //输入 
    dijkstar (st);  //最短路 
    output ();      //输出 
    return 0;
}