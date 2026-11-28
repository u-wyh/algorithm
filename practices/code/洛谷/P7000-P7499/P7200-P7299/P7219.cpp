// https://www.luogu.com.cn/problem/P7219
// 题意：N x N 网格中第 i 列底部 1..A_i 行为障碍，
// 另有 M 颗位于 (X_i, Y_i)（Y_i > A_{X_i}）的星星
// 删去第 i 颗代价 C_i；
// 求使网格中不存在不含障碍且至少含 2 颗星星的子矩形的最小总代价。
// 数据范围：1 <= N, M <= 2*10^5，
// 1 <= A_i, X_i, Y_i <= N，1 <= C_i <= 10^9
// A_{X_i} < Y_i，无重合星星。
// 难度评分：2500（洛谷分级换算）
// 算法标签：树状数组、贪心、扫描线
#include <bits/stdc++.h>
using namespace std;

const int N = 400005;
typedef long long ll;

// 树状数组类，用于维护区间和
ll tree[N];
int n;

// 树状数组的lowbit函数
int lowbit(int x) {
    return x & (-x);
}

// 初始化树状数组，大小为n0
void init_tree(int n0) {
    n = n0;
    for (int i = 0; i <= n; i++) {
        tree[i] = 0;
    }
}

// 更新树状数组，在位置p加上值x
void update_tree(int p, ll x) {
    while (p <= n) {
        tree[p] += x;
        p += lowbit(p);
    }
}

// 查询树状数组前缀和[1, p]
ll query_tree(int p) {
    ll res = 0;
    while (p) {
        res += tree[p];
        p -= lowbit(p);
    }
    return res;
}

// 星星结构体
struct Star {
    int x, y, c;
    // 按y坐标从小到大排序
    bool operator<(const Star& s) const {
        return y < s.y;
    }
};

Star stars[N];      // 存储所有星星
pair<int, int> ships[N]; // 存储小白船的高度和列索引
set<int> available_cols; // 可用列的集合（当前没有被小白船阻挡的列）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n_val;
    cin >> n_val;
    // 读取小白船高度，并存储为(高度, 列索引)对
    for (int i = 1; i <= n_val; i++) {
        cin >> ships[i].first;
        ships[i].second = i;
    }
    // 按小白船高度排序
    sort(ships + 1, ships + n_val + 1);
    
    int m;
    cin >> m;
    // 读取所有星星
    for (int i = 1; i <= m; i++) {
        cin >> stars[i].x >> stars[i].y >> stars[i].c;
    }
    // 按星星的y坐标排序
    sort(stars + 1, stars + m + 1);
    
    // 初始化可用列集合，初始包含所有列
    for (int i = 1; i <= n_val; i++) {
        available_cols.insert(i);
    }
    // 添加边界值
    available_cols.insert(0);
    available_cols.insert(n_val + 1);
    
    // 初始化树状数组
    init_tree(n_val);
    
    int ship_idx = 0; // 已处理的小白船索引
    ll total_cost = 0; // 总删除代价
    
    // 按y坐标从小到大处理每个星星
    for (int i = 1; i <= m; i++) {
        int x = stars[i].x;
        int y = stars[i].y;
        int c = stars[i].c;
        
        // 移除高度小于当前星星y坐标的小白船（它们不会阻挡当前星星）
        while (ship_idx < n_val && ships[ship_idx + 1].first < y) {
            available_cols.erase(ships[++ship_idx].second);
        }
        
        // 找到当前星星所在的连续区间边界
        auto it = available_cols.lower_bound(x);
        int right_bound = *it - 1; // 右边界
        it--;
        int left_bound = *it + 1;  // 左边界
        
        // 查询当前星星位置的代价差值
        ll cost_diff = query_tree(x);
        
        // 决策：删除当前星星还是删除限制它的星星
        if (c < cost_diff) {
            // 删除当前星星代价更小
            total_cost += c;
        } else {
            // 删除限制星星代价更小
            total_cost += cost_diff;
            // 更新树状数组，反映反悔决策
            update_tree(left_bound, c - cost_diff);
            update_tree(right_bound + 1, cost_diff - c);
        }
    }
    
    cout << total_cost << endl;
    
    return 0;
}