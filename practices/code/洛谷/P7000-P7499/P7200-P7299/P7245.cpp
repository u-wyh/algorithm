// https://www.luogu.com.cn/problem/P7245
// 题意：n x n 初始全 0 矩阵，
// 给定递增序列 x_1..x_m 与
// y_1..y_m（0 <= x_1,y_1 且 x_m,y_m <= n）。
// 共 k 次操作，
// 每次随机选 1 <= i_1 < i_2 <= m 和
// 1 <= j_1 < j_2 <= m
// 将子矩阵 [x_{i_1}+1..x_{i_2}] x
// [y_{j_1}+1..y_{j_2}] 异或 1；
// 求 k 次后矩阵元素和的期望，对 998244353 取模。
// 数据范围：1 <= n <= 10^9，
// 2 <= m <= min(n+1, 10^3)，
// 1 <= k <= 10^6，x_i 与 y_i 严格递增。
// 算法标签：最小费用最大流、离散化、差分
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;

struct edge {
    int nxt, to, weight, val;
} e[MAXN << 2];

int T, n, a, b, tot, s, t;
int h[MAXN], cur[MAXN], dep[MAXN], cost;
int node[MAXN], cnt, plane[MAXN][3], sum[MAXN];
double p;
bool vis[MAXN];

inline void add(int x, int y, int w, int val) {
    e[++tot].nxt = h[x];
    h[x] = tot;
    e[tot].to = y;
    e[tot].weight = w;
    e[tot].val = val;
    
    e[++tot].nxt = h[y];
    h[y] = tot;
    e[tot].to = x;
    e[tot].weight = 0;
    e[tot].val = -val;
}

inline bool SPFA() {
    for(int i = 0; i <= t; ++i) {
        vis[i] = false;
        dep[i] = INF;
        cur[i] = h[i];
    }
    queue<int> q;
    q.push(s);
    dep[s] = 0;
    
    while(!q.empty()) {
        int k = q.front();
        q.pop();
        vis[k] = false;
        
        for(int i = h[k]; i; i = e[i].nxt) {
            if(e[i].weight && dep[e[i].to] > dep[k] + e[i].val) {
                dep[e[i].to] = dep[k] + e[i].val;
                if(!vis[e[i].to]) {
                    vis[e[i].to] = true;
                    q.push(e[i].to);
                }
            }
        }
    }
    return dep[t] != INF;
}

int dfs(int k, int f) {
    if(k == t) {
        vis[t] = true;
        return f;
    }
    vis[k] = true;
    int r = 0, used = 0;
    
    for(int &i = cur[k]; i; i = e[i].nxt) {
        if((!vis[e[i].to] || e[i].to == t) && e[i].weight && dep[e[i].to] == dep[k] + e[i].val) {
            if((r = dfs(e[i].to, min(e[i].weight, f - used)))) {
                e[i].weight -= r;
                e[i ^ 1].weight += r;
                used += r;
                cost += r * e[i].val;
                if(f == used) break;
            }
        }
    }
    return used;
}

inline int dinic() {
    cost = 0;
    while(SPFA()) {
        vis[t] = true;
        while(vis[t]) {
            memset(vis, false, sizeof(vis));
            dfs(s, INF);
        }
    }
    return cost;
}

void init() {
    tot = 1;
    memset(h, 0, sizeof(h));
    memset(node, 0, sizeof(node));
    memset(sum, 0, sizeof(sum));
    cnt = 0;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        init();
        scanf("%d%d%d%lf", &n, &a, &b, &p);
        
        // 读入飞机数据并收集时间点
        for(int i = 1; i <= n; ++i) {
            scanf("%d%d%d", &plane[i][0], &plane[i][1], &plane[i][2]);
            node[++cnt] = plane[i][1];
            node[++cnt] = plane[i][2];
        }
        
        // 离散化时间
        sort(node + 1, node + cnt + 1);
        cnt = unique(node + 1, node + cnt + 1) - node - 1;
        
        // 设置源点和汇点
        s = n + cnt + 1;
        t = s + 1;
        
        // 检查可行性
        bool flag = true;
        for(int i = 1; i <= n; ++i) {
            int s_idx = lower_bound(node + 1, node + cnt + 1, plane[i][1]) - node;
            int t_idx = lower_bound(node + 1, node + cnt + 1, plane[i][2]) - node;
            sum[s_idx]++;
            sum[t_idx]--;
        }
        
        for(int i = 1; i <= cnt; ++i) {
            sum[i] += sum[i - 1];
            if(sum[i] > a + b) {
                puts("impossible");
                flag = false;
                break;
            }
        }
        if(!flag) continue;
        
        // 重新初始化sum数组用于建图
        memset(sum, 0, sizeof(sum));
        
        // 建图
        // 1. 时间点之间的边（登机桥容量限制）
        for(int i = 1; i < cnt; ++i) {
            add(i, i + 1, a, 0);
        }
        
        // 2. 飞机相关的边
        for(int i = 1; i <= n; ++i) {
            int s_idx = lower_bound(node + 1, node + cnt + 1, plane[i][1]) - node;
            int t_idx = lower_bound(node + 1, node + cnt + 1, plane[i][2]) - node;
            int x = plane[i][0];
            
            // 源点到登机时间点
            add(s, s_idx, 1, 0);
            
            // 飞机点到汇点
            add(i + cnt, t, 1, 0);
            
            // 方案1：一直在摆渡车（从登机时间点直接到飞机点）
            add(s_idx, i + cnt, 1, x);
            
            // 方案2：一直在登机桥（从起飞时间点到飞机点）
            add(t_idx, i + cnt, 1, 0);
            
            // 方案3：先登机桥后摆渡车（从登机时间+1到飞机点）
            if(s_idx + 1 <= cnt) {
                add(s_idx + 1, i + cnt, 1, (int)floor(x * p + 1e-5));
            }
        }
        
        printf("%d\n", dinic());
    }
    return 0;
}