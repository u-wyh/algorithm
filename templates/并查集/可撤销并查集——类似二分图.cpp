// 团建，C++版
// 一共有n个人，每个人给定组号，一共有m条边，代表两人之间有矛盾
// 一共有k个小组，可能有的组没人，但是组依然存在
// 假设组a和组b，两个组的人一起去团建，组a和组b的所有人，可以重新打乱
// 如果所有人最多分成两个集团，每人都要参加划分，并且每个集团的内部不存在矛盾
// 那么组a和组b就叫做一个"合法组对"，注意，组b和组a就不用重复计算了
// 一共有k个组，随意选两个组的情况很多，计算一共有多少个"合法组对"
// 1 <= n、m、k <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/CF1444C
// 测试链接 : https://codeforces.com/problemset/problem/1444/C
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int n, m, k;
// 每个节点的组号
int team[MAXN];
// 每条边有两个端点
int edge[MAXN][2];

// 两个端点为不同组的边，u、uteam、v、vteam
struct CrossEdge {
    int u, uteam, v, vteam;
};
bool CrossEdgeCmp(CrossEdge x, CrossEdge y) {
    if(x.uteam != y.uteam) {
    	return x.uteam < y.uteam;
    } else {
    	return x.vteam < y.vteam;
    }
}
CrossEdge crossEdge[MAXN];
int cnt = 0;

// conflict[i] = true，表示i号组自己去划分二分图，依然有冲突
// conflict[i] = false，表示i号组自己去划分二分图，没有冲突
bool conflict[MAXN];

// 可撤销并查集
int father[MAXN << 1];
int siz[MAXN << 1];
int rollback[MAXN << 1][2];
int opsize;

int find(int i) {
    while (i != father[i]) {
        i = father[i];
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
    rollback[++opsize][0] = fx;
    rollback[opsize][1] = fy;
}

void undo() {
    int fx = rollback[opsize][0];
    int fy = rollback[opsize--][1];
    father[fy] = fy;
    siz[fx] -= siz[fy];
}

void filter() {
    for (int i = 1; i <= 2 * n; ++i) {
        //相当于加一倍  1 <-> 1'
        father[i] = i;
        siz[i] = 1;
    }
    for (int i = 1, u, v; i <= m; i++) {
        u = edge[i][0];
        v = edge[i][1];
        if (team[u] < team[v]) {
            //如果这条边的两个点不是一个组
            //那么统计于不同组的边集
            crossEdge[++cnt].u = u;
            crossEdge[cnt].uteam = team[u];
            crossEdge[cnt].v = v;
            crossEdge[cnt].vteam = team[v];
        } else if (team[u] > team[v]) {
            crossEdge[++cnt].u = v;
            crossEdge[cnt].uteam = team[v];
            crossEdge[cnt].v = u;
            crossEdge[cnt].vteam = team[u];
        } else {
            //否则判断这个组能否成为可以选择的组
            if (conflict[team[u]]) {
                continue;
            }
            if (find(u) == find(v)) {
                k--;
                conflict[team[u]] = true;
                //表示这个组就会存在矛盾 直接不用考虑
            } else {
                //否则相当于正反集
            	Union(u, v + n);
            	Union(v, u + n);
            }
        }
    }
}

long long compute() {
    sort(crossEdge + 1, crossEdge + cnt + 1, CrossEdgeCmp);
    //按照较小的那个节点所造集合排序
    long long ans = (long long)k * (k - 1) / 2;//全部组对有多少
    int u, uteam, v, vteam, unionCnt;
    for (int l = 1, r = 1; l <= cnt; l = ++r) {
        uteam = crossEdge[l].uteam;
        vteam = crossEdge[l].vteam;
        while (r + 1 <= cnt && crossEdge[r + 1].uteam == uteam && crossEdge[r + 1].vteam == vteam) {
            //将两个点所在结合相同的边划分为一个组
            r++;
        }
        if (conflict[uteam] || conflict[vteam]) {
            //这个组如果本身就是不合法的  直接淘汰
            //对答案也不会有影响 因为一开始的k就减少了
            continue;
        }
        unionCnt = 0;
        for (int i = l; i <= r; i++) {
            u = crossEdge[i].u;
            v = crossEdge[i].v;
            if (find(u) == find(v)) {
                //如果不合法
                ans--;
                break;
            } else {
            	Union(u, v + n);
            	Union(v, u + n);
                unionCnt += 2;//注意这里是两步
            }
        }
        for (int i = 1; i <= unionCnt; i++) {
            undo();
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> team[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> edge[i][0] >> edge[i][1];
    }
    filter();
    cout << compute() << "\n";
    return 0;
}