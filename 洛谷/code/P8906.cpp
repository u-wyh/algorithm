#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

typedef long long ll;
const int MAXN = 305;
const int MAXK = 10;
const ll INF = 0x3f3f3f3f3f3f3f3fLL;

int N, K;
ll w[MAXN][MAXN];          // 存储边的权重
int edges[MAXN*MAXN][2];   // 存储删除边的顺序
ll F[MAXK][MAXN];          // DP数组，F[k][i]表示从节点0到节点i经过k条边的最短路径
ll A[MAXN][MAXN];          // 当前图中存在的边的权重
queue<int> changed[MAXK];  // 用于每层k的BFS传播的队列
bool inQueue[MAXK][MAXN];  // 标记节点是否在队列中
ll output[MAXN*MAXN+1];    // 存储每次删除边后的答案

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 读取输入
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> w[i][j];
        }
    }
    for (int i = 0; i < N*N; i++) {
        int u, v;
        cin >> u >> v;
        edges[i][0] = u - 1;  // 转换为0-indexed
        edges[i][1] = v - 1;
    }

    // 初始化DP数组和邻接矩阵A
    for (int k = 0; k <= K; k++) {
        for (int i = 0; i < N; i++) {
            F[k][i] = INF;
        }
    }
    F[0][0] = 0;  // 起点到自身经过0条边的距离为0

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = INF;  // 初始时所有边都不存在
        }
    }

    // 从最后一条被删除的边开始逆向添加
    for (int idx = N*N - 1; idx >= 0; idx--) {
        int u = edges[idx][0];
        int v = edges[idx][1];
        ll weight = w[u][v];
        A[u][v] = weight;  // 添加边(u, v)到图中

        // 检查新添加的边是否可以直接更新F数组
        for (int k = 1; k <= K; k++) {
            if (F[k-1][u] < INF) {
                ll new_val = F[k-1][u] + weight;
                if (new_val < F[k][v]) {
                    F[k][v] = new_val;
                    if (!inQueue[k][v]) {
                        changed[k].push(v);
                        inQueue[k][v] = true;
                    }
                }
            }
        }

        // 传播更新：处理每层k的队列，更新k+1层
        for (int k = 1; k < K; k++) {
            while (!changed[k].empty()) {
                int i = changed[k].front(); 
                changed[k].pop();
                inQueue[k][i] = false;
                for (int j = 0; j < N; j++) {
                    if (A[i][j] < INF) {
                        ll new_val = F[k][i] + A[i][j];
                        if (new_val < F[k+1][j]) {
                            F[k+1][j] = new_val;
                            if (!inQueue[k+1][j]) {
                                changed[k+1].push(j);
                                inQueue[k+1][j] = true;
                            }
                        }
                    }
                }
            }
        }

        // 存储当前状态的答案：从节点0到节点N-1经过K条边的最短路径
        output[idx] = (F[K][N-1] == INF) ? -1 : F[K][N-1];
    }

    // 输出每次删除边后的答案
    for (int i = 0; i < N*N; i++) {
        cout << output[i] << '\n';
    }

    return 0;
}