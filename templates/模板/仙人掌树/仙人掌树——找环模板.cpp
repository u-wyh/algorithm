// 仙人掌遍历和找环的过程，C++版

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;
const int MAXM = 200001;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cntg;

int dfn[MAXN];
int low[MAXN];
int cntd;
int sta[MAXN];
int top;

// 这里的from数组  一般用于记录每个点通过那条边实现的访问
// 可以复用 其实一般复用的就是入环顶点
// 这里的信息应该是自己作为环中点而不是入环顶点（如果在环的时候）  以及不在环中的时候
int fromWeight[MAXN];

void tarjan(int u, int preEdge) {
    dfn[u] = low[u] = ++cntd;
    sta[++top] = u;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        if ((e ^ 1) == preEdge) continue;
        int v = to[e], w = weight[e];
        if (dfn[v] == 0) {
            // 注意这里设置信息是在tarjan函数之后
            tarjan(v, e);
            fromWeight[v] = w; // 设置v的from信息
            if (low[v] < dfn[u]) { // 没有扎起口袋
                low[u] = min(low[u], low[v]);
            } else if (low[v] > dfn[u]) {
                // 发现割边，实现有关割边的处理
                // 对于割边 实际上采用的是树的处理方式
                top--;
            } else {
                // 发现了环，实现有关环的处理
            }
        } else {
            if (dfn[v] < dfn[u]) { // 发现回边
                fromWeight[v] = w; // 闭合边的信息给入环节点
                low[u] = min(low[u], dfn[v]);
            }
            // 如果发现弃边，一般什么也不做
        }
    }
}