// 可撤销并查集模版题，C++版
// 一共有n个点，每个点有两个小球，每个点给定两个小球的编号
// 一共有n-1条无向边，所有节点连成一棵树
// 对i号点，2 <= i <= n，都计算如下问题的答案并打印
// 从1号点到i号点的最短路径上，每个点只能拿一个小球，最多能拿几个编号不同的小球
// 1 <= n <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/AT_abc302_h
// 测试链接 : https://atcoder.jp/contests/abc302/tasks/abc302_h
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题之所以要使用可撤销并查集  是因为需要回溯操作
// 这道题两个并查集合并的时候，会不会出现一个集合中边比较少（还可以加边）但是另外一个集合中边的数量太多
// 然后继续与别的集合合并的时候,导致机会浪费?
// 实际上是不可能的，因为两个集合合并的时候集合的边数至少是点数-1  要不然不可能形成一个集合
// 那么这样两个集合合并的时候，那个边数是点数-1的相当于是加上了一条边
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;

//表示每个节点上的两个小球的编号
int arr[MAXN][2];

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cnt;

//表示父亲信息
int father[MAXN];
//表示数组大小
int siz[MAXN];
//表示这个集合中的边数
int edgeCnt[MAXN];

//利用数组完成栈的功能
int rollback[MAXN][2];
int opsize = 0;//表示栈的大小

int ans[MAXN];
int ball = 0;

void addEdge(int u, int v) {
	nxt[++cnt] = head[u];
	to[cnt] = v;
    head[u] = cnt;
}

int find(int i) {
	while(i != father[i]) {
		i = father[i];//注意这里没有扁平化
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
    edgeCnt[fx] += edgeCnt[fy] + 1;//这道题特有操作
    //加入栈中  方便返回
    rollback[++opsize][0] = fx;
    rollback[opsize][1] = fy;
}

void undo() {
    //撤销一步操作
    int fx = rollback[opsize][0];
    int fy = rollback[opsize--][1];
    father[fy] = fy;
    siz[fx] -= siz[fy];
    edgeCnt[fx] -= edgeCnt[fy] + 1;
}

void dfs(int u, int fa) {
    int fx = find(arr[u][0]);
    int fy = find(arr[u][1]);
    bool added = false;
    bool unioned = false;
    if (fx == fy) {
        //在同一个集合里  如果边数不满 那么球的数量可以加一
        if (edgeCnt[fx] < siz[fx]) {
            ball++;
            added = true;//打标记
        }
        edgeCnt[fx]++;
    } else {
        if (edgeCnt[fx] < siz[fx]|| edgeCnt[fy] < siz[fy]) {
            //存在一个小球所在集合的边数不满 那么球的数量可以加一
            ball++;
            added = true;
        }
        Union(fx, fy);
        unioned = true;
    }
    ans[u] = ball;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        //向下递归
        if (to[e] != fa) {
            dfs(to[e], u);
        }
    }

    //回溯操作  表示这个结点不走了
    if (added) {
        ball--;
    }
    if (unioned) {
        undo();
    } else {
        //即使没有合并操作 边数还是加了一  要减回去
        edgeCnt[fx]--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i][0] >> arr[i][1];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        siz[i] = 1;
        edgeCnt[i] = 0;
    }
    dfs(1, 0);
    for (int i = 2; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << ans[n] << "\n";
    return 0;
}