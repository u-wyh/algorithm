// https://www.luogu.com.cn/problem/P3275
// 题意：给 N 个小朋友分糖果，每人至少分到 1 颗，需满足 K 条不等关系。
// X=1: A=B；X=2: A<B；X=3: A>=B；X=4: A>B；
// X=5: A<=B。
// 输出最少需要的总糖果数；若无解输出 -1。
// 数据范围：
// 1 <= N, K <= 10^5（人数与条件数）
// 1 <= X <= 5（关系类型）
// 1 <= A, B <= N（小朋友编号）
// 难度评分：2000（洛谷分级换算）
// 算法标签：差分约束、Kosaraju、动态规划
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 100005;
const int MAXE = 200005;

struct Edge{
    int from, to, weight, next, reverseNext;
};
Edge edges[MAXE];
int n, k, edgeCount;
int head[MAXN], reverseHead[MAXN];

bool visited[MAXN];
int order[MAXN], orderCount, vertexStack[MAXN], nextEdge[MAXN];
int component[MAXN], componentSize[MAXN], componentCount;
int componentHead[MAXN], componentNext[MAXE], candy[MAXN];

void addEdge(int u, int v, int w){
    edges[++edgeCount] = {u, v, w, head[u], reverseHead[v]};
    head[u] = reverseHead[v] = edgeCount;
}

void recordFinishOrder(){
    copy(head + 1, head + n + 1, nextEdge + 1);
    for(int start = 1; start <= n; ++start){
        if(visited[start]){
            continue;
        }
        int top = 1;
        vertexStack[top] = start;
        visited[start] = true;
        while(top){
            int u = vertexStack[top];
            int &e = nextEdge[u];
            if(!e){
                order[++orderCount] = u;
                --top;
                continue;
            }
            int v = edges[e].to;
            e = edges[e].next;
            if(!visited[v]){
                visited[v] = true;
                vertexStack[++top] = v;
            }
        }
    }
}

void assignComponents(){
    for(int i = orderCount; i >= 1; --i){
        int start = order[i];
        if(component[start]){
            continue;
        }
        int id = ++componentCount;
        int top = 1;
        vertexStack[top] = start;
        component[start] = id;
        while(top){
            int u = vertexStack[top--];
            ++componentSize[id];
            for(int e = reverseHead[u]; e; e = edges[e].reverseNext){
                int v = edges[e].from;
                if(!component[v]){
                    component[v] = id;
                    vertexStack[++top] = v;
                }
            }
        }
    }
}

long long minTotalCandy(){
    for(int e = 1; e <= edgeCount; ++e){
        int from = component[edges[e].from];
        int to = component[edges[e].to];
        if(from == to){
            if(edges[e].weight){
                return -1;
            }
        }else{
            componentNext[e] = componentHead[from];
            componentHead[from] = e;
        }
    }

    // Kosaraju 按缩点后的拓扑序编号，直接顺序转移。
    long long total = 0;
    for(int id = 1; id <= componentCount; ++id){
        candy[id] = max(candy[id], 1);
        total += 1LL * candy[id] * componentSize[id];
        for(int e = componentHead[id]; e; e = componentNext[e]){
            int v = component[edges[e].to];
            candy[v] = max(candy[v], candy[id] + edges[e].weight);
        }
    }
    return total;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    // 边 u -> v 表示 v 的糖果数至少为 u 的糖果数加上边权。
    for(int i = 0, type, u, v; i < k; ++i){
        cin >> type >> u >> v;
        if(type == 1){
            addEdge(u, v, 0);
            addEdge(v, u, 0);
        }else if(type == 2){
            addEdge(u, v, 1);
        }else if(type == 3){
            addEdge(v, u, 0);
        }else if(type == 4){
            addEdge(v, u, 1);
        }else{
            addEdge(u, v, 0);
        }
    }

    recordFinishOrder();
    assignComponents();
    cout << minTotalCandy() << '\n';
    return 0;
}
