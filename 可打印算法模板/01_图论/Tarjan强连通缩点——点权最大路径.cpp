// 用途：有向图先缩强连通分量，再求可重复走点的最大点权路径。
// 时间：O(n+m)；空间：O(n+m)。
// 注意：点权非负；缩点后的边允许重复，不影响答案。
// 例题：https://www.luogu.com.cn/problem/P3387
// 原代码：P3387.cpp；保留原来的两种 DAG 转移写法。
// 题意：经过点可得一次点权，允许重复经过，求能得到的最大点权和。
// 思路：每个强连通分量内的点都能走到；合并点权后，在缩点 DAG 上求最长路。

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10001;
const int MAXM = 100001;
int n, m;

int arr[MAXN];
int a[MAXM];
int b[MAXM];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg;

int dfn[MAXN];
int low[MAXN];
int cntd;

int sta[MAXN];
int top;

int belong[MAXN];
int sum[MAXN];
int sccCnt;

int indegree[MAXN];
int que[MAXN];
int dp[MAXN];

void addEdge(int u, int v) {
   nxt[++cntg] = head[u];
   to[cntg] = v;
   head[u] = cntg;
}

void tarjan(int u) {
   dfn[u] = low[u] = ++cntd;
   sta[++top] = u;
   for (int e = head[u]; e > 0; e = nxt[e]) {
       int v = to[e];
       if (dfn[v] == 0) {
           tarjan(v);
           low[u] = min(low[u], low[v]);
       } else {
           if (belong[v] == 0) {
               low[u] = min(low[u], dfn[v]);
           }
       }
   }
   if (dfn[u] == low[u]) { // u 是强连通分量根：弹栈并累加这一块的点权。
       sccCnt++;
       int pop;
       do {
           pop = sta[top--];
           belong[pop] = sccCnt;
           sum[sccCnt] += arr[pop];
       } while (pop != u);
   }
}

void condense() {
   // 原图边转为分量间的边；分量内部边丢弃。
   cntg = 0;
   for (int i = 1; i <= sccCnt; i++) {
       head[i] = 0;
   }
   for (int i = 1; i <= m; i++) {
       int scc1 = belong[a[i]];
       int scc2 = belong[b[i]];
       if (scc1 != scc2) {
           indegree[scc2]++;
           addEdge(scc1, scc2);
       }
   }
}

int topo() {
   int l = 1, r = 0;
   for (int i = 1; i <= sccCnt; i++) {
       if (indegree[i] == 0) {
           dp[i] = sum[i];
           que[++r] = i;
       }
   }
   while (l <= r) {
       int u = que[l++];
       for (int e = head[u]; e > 0; e = nxt[e]) {
           int v = to[e];
           dp[v] = max(dp[v], dp[u] + sum[v]);
           if (--indegree[v] == 0) {
               que[++r] = v;
           }
       }
   }
   int ans = 0;
   for (int i = 1; i <= sccCnt; i++) {
       ans = max(ans, dp[i]);
   }
   return ans;
}

int dpOnDAG() {
   // Tarjan 弹栈得到的分量编号满足：跨分量边 scc1 -> scc2 时 scc1 > scc2。
   // 所以按分量编号从大到小转移，等价于 DAG 拓扑顺序。
   for (int u = sccCnt; u > 0; u--) {
       if (indegree[u] == 0) {
           dp[u] = sum[u];
       }
       for (int e = head[u]; e > 0; e = nxt[e]) {
           int v = to[e];
           dp[v] = max(dp[v], dp[u] + sum[v]);
       }
   }
   int ans = 0;
   for (int u = 1; u <= sccCnt; u++) {
       ans = max(ans, dp[u]);
   }
   return ans;
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   cin >> n >> m;
   for (int i = 1; i <= n; i++) {
       cin >> arr[i];
   }
   for (int i = 1; i <= m; i++) {
       cin >> a[i] >> b[i];
       addEdge(a[i], b[i]);
   }
   for (int i = 1; i <= n; i++) {
       if (dfn[i] == 0) {
           tarjan(i);
       }
   }
   condense();
   // int ans = topo();
   int ans = dpOnDAG();
   cout << ans << "\n";
   return 0;
}
