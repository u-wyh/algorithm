// 同在最小生成树里，C++版
// 一共有n个点，m条无向边，每条边有边权，图保证是连通的
// 一共有q次查询，每条查询都给定参数k，表示该查询涉及k条边
// 然后依次给出k条边的编号，打印这k条边能否同时出现在一颗最小生成树上
// 1 <= n、m、q、所有查询涉及边的总量 <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/CF891C
// 测试链接 : https://codeforces.com/problemset/problem/891/C
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这里其实用到了kruskal生成树中的一个性质：
//对于所有边权相同的边  不论按照什么顺序  最终得到的连通性都是一样的
//这里指的不是说最终选的边是一样的（也就是选择的边是固定的）  而是说他们所形成的联通块中的点是一样的
//即如果1 2这两个节点以某种边顺序的情况下  是联通的  那么在其他顺序遍历完相同的边权后  也一定是联通的

//这道题的逻辑是 所有的边按照边权先排序
//所有问题涉及到的边全部收集起来 也按照边权排序  然后将是同一个问题的边划分为一个组
//每次将小于这个组的边全部按照kruskal建立最小生成树  然后判断这个组里面的边能否进入最小生成树  不能那么这个组所属于的问题答案就是false
//然后将这个组加入的信息全部回退  因为后面一个组可能边权和这个组一样 只不过是所属问题号不同  为了消除对后面的影响
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int n, m, q, k;

struct Edge {
    int u, v, w;
};

bool EdgeCmp(Edge x, Edge y) {
    return x.w < y.w;
}

struct Query {
    int u, v, w, i;
};

bool QueryCmp(Query x, Query y) {
    if(x.w != y.w) {
        return x.w < y.w;
    } else {
        return x.i < y.i;
    }
}

Edge edge[MAXN];
Query queries[MAXN];

int father[MAXN];
int siz[MAXN];
//栈
int rollback[MAXN << 1][2];
int opsize;

bool ans[MAXN];

int find(int i) {
    while (i != father[i]) {
        i = father[i];//没有扁平化
    }
    return i;
}

void Union(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (siz[fx] < siz[fy]) {
        int tmp = fx;
        fx = fy;
        fy = tmp;
    }
    father[fy] = fx;
    siz[fx] += siz[fy];
    //将操作入栈
    rollback[++opsize][0] = fx;
    rollback[opsize][1] = fy;
}

void undo() {
    int fx = rollback[opsize][0];
    int fy = rollback[opsize--][1];
    father[fy] = fy;
    siz[fx] -= siz[fy];
}

void prepare() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        siz[i] = 1;
    }
    sort(edge + 1, edge + m + 1, EdgeCmp);//所有的边按照边权排序
    sort(queries + 1, queries + k + 1, QueryCmp);//所有的问题按照边权和问题号排序
    for (int i = 1; i <= q; i++) {
        ans[i] = true;
    }
}

void compute() {
    int ei = 1, queryId, unionCnt;
    for (int l = 1, r = 1; l <= k; l = ++r) {
        while (r + 1 <= k && queries[l].w == queries[r + 1].w && queries[l].i == queries[r + 1].i) {
            //将问题分组
            r++;
        }
        // 将权值小于目前查询的边全部加进去  
        for (; ei <= m && edge[ei].w < queries[l].w; ei++) {
            if (find(edge[ei].u) != find(edge[ei].v)) {
                Union(edge[ei].u, edge[ei].v);
            }
        }
        queryId = queries[l].i;
        if (!ans[queryId]) {
            //以前就是不对的了  那么直接结束 没有判断的必要
            continue;
        }
        unionCnt = 0;
        for (int i = l; i <= r; i++) {
            if (find(queries[i].u) == find(queries[i].v)) {
                ans[queryId] = false;
                break;
            } else {
                Union(queries[i].u, queries[i].v);
                unionCnt++;
            }
        }
        for (int i = 1; i <= unionCnt; i++) {
            //多次回溯
            undo();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
    cin >> q;
    k = 0;
    for (int i = 1, s; i <= q; i++) {
        cin >> s;
        for (int j = 1, ei; j <= s; j++) {
            cin >> ei;
            queries[++k].u = edge[ei].u;
            queries[k].v = edge[ei].v;
            queries[k].w = edge[ei].w;
            queries[k].i = i;
        }
    }
    prepare();
    compute();
    for (int i = 1; i <= q; i++) {
        if (ans[i]) {
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }
    return 0;
}