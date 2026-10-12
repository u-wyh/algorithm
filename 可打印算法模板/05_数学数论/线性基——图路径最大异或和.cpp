// 用途：求无向带权图从 1 到 n 的路径异或和最大值。
// 时间：O(nB)。
// 空间：O(B)。
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
long weight[MAXM];
int cnt=1;

// 所有环的异或和构建的线性基
long basis[BIT + 1];
// 某个节点在dfs过程中是否被访问过
bool visited[MAXN];
// 从头结点到当前节点的异或和
long path[MAXN];

void addEdge(int u, int v, long w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool insert(long num) {
    for (int i = BIT; i >= 0; i--)
        if (num >> i == 1) {
            if (basis[i] == 0) {
                basis[i] = num;
                return true;
            }
            num ^= basis[i];
        }
    return false;
}

void dfs(int u, int f, long p) {
	path[u] = p;
	visited[u] = true;
	for (int e = head[u]; e != 0; e = Next[e]) {
		int v = to[e];
		if (v != f) {
			long eor = p ^ weight[e];
			if (visited[v]) {
                //这个点访问过了  说明这就是一个环
				insert(eor ^ path[v]);
			} else {
				dfs(v, u, eor);
			}
		}
	}
}

long query(long init) {
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
        long w ;
        cin>>u>>v>>w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    dfs(1, 0, 0);
    cout<<query(path[n])<<endl;
    return 0;
}
