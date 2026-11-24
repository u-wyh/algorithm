// 用途：求无向带权图从 1 到 n 的路径异或和最大值。
// 时间：O((n+m)B)，B=61 为权值二进制位数。
// 空间：O(n+m+B)。
// 注意：图保证连通，可有重边和自环；边权最高 10^18，须用 long long。
// 例题：https://www.luogu.com.cn/problem/P4151
// 题意：求图上从 1 到 n 的路径边权异或和最大值。
// 思路：DFS 得一条基础路径，把每条环的异或值插入线性基后贪心增大答案。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50001;
const int MAXM = 200002;
const int BIT = 60;

// 链式前向星
int head[MAXN];
int Next[MAXM];
int to[MAXM];
long long weight[MAXM];
int cnt=2; // 无向边成对放在 e、e^1；0 表示空边。

// 所有环的异或和构建的线性基
long long basis[BIT + 1];
// 某个节点在dfs过程中是否被访问过
bool visited[MAXN];
// 从头结点到当前节点的异或和
long long path[MAXN];
int stk[MAXN];

void addEdge(int u, int v, long long w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool insert(long long num) {
    for (int i = BIT; i >= 0; i--)
        if ((num >> i) & 1LL) {
            if (basis[i] == 0) {
                basis[i] = num;
                return true;
            }
            num ^= basis[i];
        }
    return false;
}

void dfs(int start) {
    // 任取一棵生成树记录 1 到各点的异或值；深链用定长栈避免爆栈。
    int top = 0;
    visited[start] = true;
    stk[++top] = start;
    while (top) {
        int u = stk[top--];
        for (int e = head[u]; e; e = Next[e]) {
            int v = to[e];
            if (!visited[v]) {
                visited[v] = true;
                path[v] = path[u] ^ weight[e];
                stk[++top] = v;
            } else {
                // 非树边形成的环异或值；反向树边只产生 0。
                insert(path[u] ^ path[v] ^ weight[e]);
            }
        }
    }
}

long long query(long long init) {
    // 每个环可以让路径多绕一次，线性基贪心提高基础路径异或值。
    for (int i = BIT; i >= 0; i--) {
        init = max(init, init ^ basis[i]);
    }
    return init;
}

int main()
{
    int n ;
    int m ;
    cin>>n>>m;
    for (int i = 1; i <= m; i++) {
        int u ;
        int v ;
        long long w ;
        cin>>u>>v>>w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    dfs(1);
    cout<<query(path[n])<<endl;
    return 0;
}
