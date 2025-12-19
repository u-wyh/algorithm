#include<bits/stdc++.h>
#define int long long
using namespace std;
using i64 = long long;
const int N = 5e4 + 7, K = 37;
int f[N][K], n, k, col[N], cnt;
vector<int> e[N], vec;
struct Point {
    int x, y, z;
} p[N];

// 按y坐标排序的比较函数
struct cmp {
    bool operator () (const int &u, const int &v) const {
        return ((p[u].y == p[v].y) ? u > v : p[u].y < p[v].y);
    }
};

set <int, cmp> st;

// 计算两点距离平方（避免开方）
i64 dis (int u, int v) {
    return 0ll + 1ll * (p[u].x - p[v].x) * (p[u].x - p[v].x) + 1ll * (p[u].y - p[v].y) * (p[u].y - p[v].y);
}

// DFS找连通块
void dfs (int u) {
    col[u] = cnt; 
    vec.push_back (p[u].z);
    for (auto v : e[u]) if (! col[v]) dfs (v);
}

// 检查连通块是否存在满足条件的子集
bool subset () {
    int m = (int) vec.size ();
    if (m > k) return true;  // 鸽巢原理
    
    // 背包DP检查子集和
    for (int i = 1; i < k; i ++) f[m][i] = 0;
    f[m][0] = 1;
    
    for (int i = m - 1; ~i; i --) {
        for (int j = 0; j < k; j ++) {
            f[i][j] = f[i + 1][j];
            f[i][j] |= f[i + 1][(vec[i] + j) % k];
        }
        if (f[i + 1][vec[i]]) return true;
    }
    return false;
}

// 检查给定距离平方d是否满足条件
bool check (i64 d) {
    int sqrtd = (double) (sqrt (d) + 1);  // 实际距离
    
    // 初始化
    for (int i = 1; i <= n; i ++) e[i].clear (), col[i] = 0;
    cnt = 0; st.clear ();
    
    // 扫描线
    for (int i = 1, j = 1; i <= n; i ++) {
        // 维护滑动窗口
        for (; p[i].x - p[j].x > sqrtd and j <= i; ) 
            st.erase (j ++);
        
        if (st.empty ()) { st.insert (i); continue; }
    
        // 在y方向查找邻近点
        p[n + 1] = {0, p[i].y - sqrtd, 0};
        int res = 0;
        for (auto it = st.lower_bound (n + 1); it != st.end (); it ++) {
            auto k = *it;
            if (p[k].y - p[i].y > sqrtd) break;
            if (++ res >= 4 * k) return true;  // 鸽巢原理
            if (dis (i, k) <= d) e[i].push_back (k), e[k].push_back (i);
        }
        st.insert (i);
    }
    
    // 检查所有连通块
    for (int i = 1; i <= n; i ++) {
        vec.clear ();
        if (col[i]) continue;
        ++ cnt, dfs (i);
        if (subset ()) return true;
    }
    return false;
}

signed main () {
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) {
        cin >> p[i].x >> p[i].y >> p[i].z;
        p[i].z %= k;  // 取模简化计算
    }
    
    // 按x坐标排序
    sort (p + 1, p + n + 1, [&] (const Point &u, const Point &v) {
        return u.x == v.x ? u.y < v.y : u.x < v.x;
    });
    
    // 二分查找最小距离
    i64 l = 0, r = 1e18, ans = -1;
    while (l <= r) {
        i64 mid = (l + r) >> 1;
        if (check (mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    }   
    cout << fixed << setprecision (3) << sqrt (ans);
}