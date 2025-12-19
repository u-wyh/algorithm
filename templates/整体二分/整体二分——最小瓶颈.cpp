// 点的度都是奇数的最小瓶颈，C++版
// 一共有n个点，初始没有边，依次加入m条无向边，每条边有边权
// 每次加入后，询问是否存在一个边集，满足每个点连接的边的数量都是奇数
// 如果存在，希望边集的最大边权，尽可能小，如果不存在打印-1
// 2 <= n <= 10^5
// 1 <= m <= 3 * 10^5
// 1 <= 边权 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/CF603E
// 测试链接 : https://codeforces.com/problemset/problem/603/E
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题主要是整体二分的过程很有难度
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXM = 300001;

struct Edge {
   int x, y, w, tim, rak;
};

bool EdgeCmp(Edge a, Edge b) {
   return a.w < b.w;
}

int n, m;

// edge代表所有边依次出现
// wsort代表所有边按边权排序
// 每条边有：端点x、端点y、边权w、时序tim、边权排名rak
Edge edge[MAXM];
Edge wsort[MAXM];

// 可撤销并查集 + 节点数为奇数的连通区数量为oddnum
int oddnum;
int father[MAXN];
int siz[MAXN];
int rollback[MAXN][2];
int opsize = 0;

int ans[MAXM];

int find(int i) {
    while (i != father[i]) {
        i = father[i];//可撤销并查集  没有扁平化
    }
    return i;
}

bool Union(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx == fy) {
        return false;
    }
    if ((siz[fx] & 1) == 1 && (siz[fy] & 1) == 1) {
        oddnum -= 2;
    }
    if (siz[fx] < siz[fy]) {
        int tmp = fx;
        fx = fy;
        fy = tmp;
    }
    father[fy] = fx;
    siz[fx] += siz[fy];
    rollback[++opsize][0] = fx;
    rollback[opsize][1] = fy;
    return true;
}

void undo() {
    int fx = rollback[opsize][0];
    int fy = rollback[opsize--][1];
    father[fy] = fy;
    siz[fx] -= siz[fy];
    if ((siz[fx] & 1) == 1 && (siz[fy] & 1) == 1) {
        oddnum += 2;
    }
}

// 依次出现的边在edge里，当前来到[el..er]范围
// 权值排序后的边在wsort里，答案范围[vl..vr]，同时也是排名范围
// 调用递归的前提 : el之前，边权排名<vl的边，已经加到图里了
// 利用整体二分得到所有边的答案
void compute(int el, int er, int vl, int vr) {
    if (el > er) {
        return;
    }
    if (vl == vr) {
        for (int i = el; i <= er; i++) {
            ans[i] = vl;
        }
    } else {
        int mid = (vl + vr) >> 1;
        // 1) el之前，边权排名在[vl..mid]之间的边，加到图里，通过遍历wsort[vl..mid]来加速
        int unionCnt1 = 0;
        for (int i = vl; i <= mid; i++) {
            if (wsort[i].tim < el) {
                if (Union(wsort[i].x, wsort[i].y)) {
                    unionCnt1++;
                }
            }
        }
        // 2) 从el开始遍历，边权排名<=mid的边，加到图里，找到第一个达标的边split
        int unionCnt2 = 0;
        int split = er + 1;
        for (int i = el; i <= er; i++) {
            if (edge[i].rak <= mid) {
                if (Union(edge[i].x, edge[i].y)) {
                    unionCnt2++;
                }
            }
            if (oddnum == 0) {
                split = i;
                break;
            }
        }
        // 3) 撤销2)的效果，el之前，边权排名<=mid的边，都在图中
        for (int i = 1; i <= unionCnt2; i++) {
            undo();
        }
        // 4) 执行 compute(el, split - 1, mid + 1, vr)，此时满足子递归的前提
        compute(el, split - 1, mid + 1, vr);
        // 5) 撤销1)的效果，此时只剩下前提了，el之前，边权排名<vl的边，都在图中
        for (int i = 1; i <= unionCnt1; i++) {
            undo();
        }
        // 6) 从el开始到split之前，边权排名<vl的边，加到图里
        int unionCnt3 = 0;
        for (int i = el; i <= split - 1; i++) {
            if (edge[i].rak < vl) {
                if (Union(edge[i].x, edge[i].y)) {
                    unionCnt3++;
                }
            }
        }
        // 7) 执行 compute(split, er, vl, mid)，此时满足子递归的前提
        compute(split, er, vl, mid);
        // 8) 撤销6)的效果，回到了前提
        for (int i = 1; i <= unionCnt3; i++) {
            undo();
        }
    }
}

void prepare() {
    oddnum = n;//初始时  每一个节点算作单独一个
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        siz[i] = 1;
    }
    for (int i = 1; i <= m; i++) {
        wsort[i].x = edge[i].x;
        wsort[i].y = edge[i].y;
        wsort[i].w = edge[i].w;
        wsort[i].tim = edge[i].tim;
    }
    sort(wsort + 1, wsort + m + 1, EdgeCmp);
    // edge数组、wsort数组，每条边设置排名信息
    for (int i = 1; i <= m; i++) {
        wsort[i].rak = i;
        edge[wsort[i].tim].rak = i;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].x >> edge[i].y >> edge[i].w;
        edge[i].tim = i;
    }
    prepare();
    compute(1, m, 1, m + 1);
    for (int i = 1; i <= m; i++) {
        if (ans[i] == m + 1) {
            cout << -1 << '\n';
        } else {
            cout << wsort[ans[i]].w << '\n';
        }
    }
    return 0;
}