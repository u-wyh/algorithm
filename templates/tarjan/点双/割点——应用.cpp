// 嗅探器，C++版
// 给定一张n个点、m条边的无向图，所有节点属于一个连通区
// 给定点a和点b，如果删掉别的点能让a和b不再连通，这个点叫关键点
// 打印编号最小的关键点，不存在打印"No solution"
// 1 <= n <= 2 * 10^5
// 1 <= m <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P5058
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题的大思路是将a作为树的头节点，然后开始Tarjan
// 如果一个节点符合要求，那么他一定是一个割点，而且不能是a或者b
// 同时他不可能是根节点，因为a是根节点，那么假设这个节点是u，b节点在他的儿子v中
// 那么一定有v相对于u而言，u就是割点
// 怎么确定b在v中呢  很简单使用dfn[b]>=dfn[v]即可
// 如果b到现在为止还没有出现，那么他的dfn是0
// 如果已经出现但是在v之前  那么他的dfn一定小于v
// 所以这个条件可以用于判断
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200001;
const int MAXM = 500001;
int n, a, b;

int head[MAXN];
int nxt[MAXM << 1];
int to[MAXM << 1];
int cntg;

int dfn[MAXN];
int low[MAXN];
int cntd;

bool isKey[MAXN];

void addEdge(int u, int v) {
   nxt[++cntg] = head[u];
   to[cntg] = v;
   head[u] = cntg;
}

void tarjan(int u) {
   dfn[u] = low[u] = ++cntd;
   for (int e = head[u]; e > 0; e = nxt[e]) {
       int v = to[e];
       if (dfn[v] == 0) {
           tarjan(v);
           low[u] = min(low[u], low[v]);
           if (low[v] >= dfn[u] && u != a && u != b && dfn[b] >= dfn[v]) {
               isKey[u] = true;
           }
       } else {
           low[u] = min(low[u], dfn[v]);
       }
   }
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   cin >> n;
   int u, v;
   cin >> u >> v;
   while (u != 0 || v != 0) {
       addEdge(u, v);
       addEdge(v, u);
       cin >> u >> v;
   }
   cin >> a >> b;
   tarjan(a);
   int ans = 0;
   for (int i = 1; i <= n; i++) {
       if (isKey[i]) {
           ans = i;
           break;
       }
   }
   if (ans == 0) {
       cout << "No solution" << "\n";
   } else {
       cout << ans << "\n";
   }
   return 0;
}