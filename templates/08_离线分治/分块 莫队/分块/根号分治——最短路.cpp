// 雅加达的摩天楼，C++版
// 有n个大楼，编号0~n-1，有m个狗子，编号0~m-1
// 每只狗子有两个参数，idx表示狗子的初始大楼，jump表示狗子的跳跃能力
// 狗子在i位置，可以来到 i - jump 或 i + jump，向左向右自由跳跃，但不能越界
// 0号狗子有消息希望传给1号狗子，所有狗子都可帮忙，返回至少传送几次，无法送达打印-1
// 1 <= n、m <= 30000
// 测试链接 : https://www.luogu.com.cn/problem/P3645
// 测试链接 : https://uoj.ac/problem/111
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题做法其实是没有用到根号分治的   是时间复杂度分析用到了根号分治
// 我们将每一个大楼看成一个节点 这个节点中的狗子其实是不重要的  重要的是他们的跳跃能力
// 所以我们使用bfs最短路求解
// 时间复杂度分析  对于跳跃能力大于根号n的  那么最多有根号n个楼里面 可以获得他的跳跃能力  并且最多只会有m只狗子
// 对于跳跃能力小于根号n的  最多也就是n个楼  所以时间复杂度可以接受
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 30001;

int n, m;
// 每个大楼拥有的狗子列表
int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt;

// 01bfs
struct Node {
    int idx, jump, time;
};
deque<Node> que;
// vis[idx]是个位图，可以表示vis[idx][jump]是否出现过
bitset<MAXN> vis[MAXN];

void add(int idx, int jump) {
    nxt[++cnt] = head[idx];
    to[cnt] = jump;
    head[idx] = cnt;
}

void trigger(int idx, int time) {
    // 驱动力得到解放  这个楼的跳跃能力可以施展
    for (int e = head[idx], jump; e; e = nxt[e]) {
        jump = to[e];
        if (!vis[idx].test(jump)) {
            vis[idx].set(jump);
            que.push_back({idx, jump, time});
        }
    }
    // 不会重复使用
    head[idx] = 0;
}

void extend(int idx, int jump, int time) {
    trigger(idx, time);
    if (!vis[idx].test(jump)) {
        // 以前没有这样的跳跃能力  或者是没有驱动力
        vis[idx].set(jump);
        que.push_back({idx, jump, time});
    }
}

int bfs(int s, int t) {
    if (s == t) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        vis[i].reset();
    }
    que.clear();
    // 放入起始点
    trigger(s, 0);
    while (!que.empty()) {
        Node cur = que.front();
        que.pop_front();
        int idx = cur.idx;
        int jump = cur.jump;
        int time = cur.time;
        if (idx - jump == t || idx + jump == t) {
            return time + 1;
        }
        // 表示这个继续跳跃
        if (idx - jump >= 0) {
            extend(idx - jump, jump, time + 1);
        }
        if (idx + jump < n) {
            extend(idx + jump, jump, time + 1);
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    int s, sjump, t, tjump;
    cin >> s >> sjump >> t >> tjump;
    add(s, sjump);
    add(t, tjump);
    for (int i = 2, idx, jump; i < m; i++) {
        cin >> idx >> jump;
        add(idx, jump);
    }
    cout << bfs(s, t) << '\n';
    return 0;
}