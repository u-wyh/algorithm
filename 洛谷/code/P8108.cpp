#include <bits/stdc++.h>
using namespace std;

// 快速读入整数函数
inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * w;
}

const int MAXN = 1003;
int tree[MAXN], n;  // tree: 树状数组，n: 网格大小
int a[MAXN][MAXN];  // 存储网格数据，a[列][行]
vector<int> v[MAXN][MAXN];  // v[列][颜色]存储该颜色在该列中的行位置

// 树状数组更新函数：在位置x更新最大值k
void add(int x, int k) {
    while (x <= n) {
        tree[x] = max(tree[x], k);  // 维护最大值
        x += x & -x;  // 跳转到父节点
    }
}

// 树状数组查询函数：查询[1,x]范围内的最大值
int find(int x) {
    int res = 0;
    while (x) {
        res = max(res, tree[x]);  // 取最大值
        x -= x & -x;  // 跳转到前一个区间
    }
    return res;
}

int main() {
    n = read();  // 读取网格大小n
    
    // 读取网格数据并预处理
    // 注意：j从n到1，表示从底部到顶部读取
    for (int j = n; j >= 1; --j) {
        for (int i = 1; i <= n; ++i) {
            // 读取颜色值并记录位置
            v[i][a[i][j] = read()].push_back(j);
        }
    }

    int ans = n * n;  // 初始答案为最坏情况下的操作次数（每个珠子单独消除）
    
    // 遍历所有相邻的列对 (i, i+1)
    for (int i = 1; i < n; ++i) {
        // 清空树状数组，为新的列对做准备
        fill(tree + 1, tree + n + 1, 0);
        int q = 0;  // 记录当前列对的最长公共子序列长度
        
        // 按第i+1列的顺序处理（从顶部到底部，即j=1到n）
        for (int j = 1; j <= n; ++j) {
            vector<pair<int, int>> z;  // 临时存储匹配的位置和对应的DP值
            
            // 在第i列中查找与第i+1列当前位置颜色相同的位置
            for (int k : v[i][a[i + 1][j]]) {
                // 对于每个匹配位置k，查询[1,k-1]范围内的最大DP值
                z.emplace_back(k, find(k - 1));
            }
            
            // 处理所有匹配位置
            for (auto &k : z) {
                // 更新最长公共子序列长度
                q = max(q, k.second + 1);
                // 更新树状数组：在位置k处记录新的DP值
                add(k.first, k.second + 1);
            }
        }
        
        // 从总操作次数中减去这一对列的最长公共子序列长度
        // 因为每对匹配的珠子可以减少一次操作
        ans -= q;
    }
    
    // 输出最终的最小操作次数
    printf("%d\n", ans);
    return 0;
}