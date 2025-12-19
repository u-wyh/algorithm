#include <bits/stdc++.h>
using namespace std;

#define uint unsigned int
const int N = 400005;  // 最大可能的数据规模
const int B = 450;     // 莫队算法的块大小，约为sqrt(N)

int n, m, q;          // n: 数组大小, m: 操作数量, q: 查询数量
int op[N], x[N], y[N];// 存储操作类型和参数
uint a[N];            // 存储数组的值
uint cur, ans[N];     // cur: 当前查询结果, ans: 存储每个查询的答案
uint pos[N], rev[N], add[N]; // 关键数组: pos[i]表示原位置i的当前位置, rev[i]表示当前位置i的原位置, add[i]表示位置i被查询的次数

// 查询结构体，用于莫队算法
struct Query {
    int l, r, blk, id; // 查询区间[l, r], 所属块blk, 查询id
    bool operator < (const Query &other) const {
        if (blk != other.blk) return blk < other.blk; // 先按块排序
        return (blk & 1) ? (r > other.r) : (r < other.r); // 奇偶块排序优化
    }
} queries[N];

int main() {
    // 读入初始数据
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%u", &a[i]);
    }
    
    int original_n = n; // 保存原始数组大小
    
    // 处理操作序列
    for (int i = 1; i <= m; i++) {
        scanf("%d", &op[i]);
        if (op[i] == 1) {
            // 将单点修改操作转换为交换操作
            scanf("%d", &x[i]);
            scanf("%u", &a[++n]); // 创建新位置存储修改值
            y[i] = n;             // 记录新位置
            op[i] = 2;            // 将操作类型改为交换
        } else if (op[i] == 2) {
            scanf("%d %d", &x[i], &y[i]);
        } else if (op[i] == 3) {
            scanf("%d", &x[i]);
        }
    }

    // 初始化位置映射数组
    for (int i = 1; i <= n; i++) {
        pos[i] = i; // 原位置i的当前位置是i
        rev[i] = i; // 当前位置i的原位置是i
    }

    // 读入查询
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", &queries[i].l, &queries[i].r);
        queries[i].blk = queries[i].l / B; // 计算所属块
        queries[i].id = i;                 // 记录查询id
    }
    
    // 按块排序查询
    sort(queries + 1, queries + q + 1);

    // 莫队算法处理查询
    int l = 1, r = 0; // 当前处理的区间[l, r]
    for (int i = 1; i <= q; i++) {
        int L = queries[i].l, R = queries[i].r;
        
        // 右指针向右扩展
        while (r < R) {
            r++;
            if (op[r] == 2) {
                // 交换操作: 交换两个位置的值和映射关系
                swap(a[x[r]], a[y[r]]);
                swap(rev[x[r]], rev[y[r]]);
                swap(add[x[r]], add[y[r]]);
                swap(pos[rev[x[r]]], pos[rev[y[r]]]);
            } else {
                // 查询操作: 增加查询次数并累加结果
                add[x[r]]++;
                cur += a[x[r]];
            }
        }
        
        // 左指针向左扩展
        while (l > L) {
            l--;
            if (op[l] == 2) {
                // 交换操作: 交换原位置的映射关系
                swap(pos[x[l]], pos[y[l]]);
                swap(a[pos[x[l]]], a[pos[y[l]]]);
                swap(rev[pos[x[l]]], rev[pos[y[l]]]);
                
                // 更新交换后的贡献变化
                cur += add[pos[x[l]]] * (a[pos[x[l]]] - a[pos[y[l]]]);
                cur += add[pos[y[l]]] * (a[pos[y[l]]] - a[pos[x[l]]]);
            } else {
                // 查询操作: 增加查询次数并累加结果
                add[pos[x[l]]]++;
                cur += a[pos[x[l]]];
            }
        }
        
        // 右指针向左收缩
        while (r > R) {
            if (op[r] == 2) {
                // 交换操作: 撤销交换
                swap(a[x[r]], a[y[r]]);
                swap(rev[x[r]], rev[y[r]]);
                swap(add[x[r]], add[y[r]]);
                swap(pos[rev[x[r]]], pos[rev[y[r]]]);
            } else {
                // 查询操作: 减少查询次数并减去结果
                add[x[r]]--;
                cur -= a[x[r]];
            }
            r--;
        }
        
        // 左指针向右收缩
        while (l < L) {
            if (op[l] == 2) {
                // 交换操作: 先计算贡献变化，再撤销交换
                cur -= add[pos[x[l]]] * (a[pos[x[l]]] - a[pos[y[l]]]);
                cur -= add[pos[y[l]]] * (a[pos[y[l]]] - a[pos[x[l]]]);
                
                swap(pos[x[l]], pos[y[l]]);
                swap(a[pos[x[l]]], a[pos[y[l]]]);
                swap(rev[pos[x[l]]], rev[pos[y[l]]]);
            } else {
                // 查询操作: 减少查询次数并减去结果
                add[pos[x[l]]]--;
                cur -= a[pos[x[l]]];
            }
            l++;
        }
        
        // 记录当前查询的答案
        ans[queries[i].id] = cur;
    }

    // 输出所有查询结果
    for (int i = 1; i <= q; i++) {
        printf("%u\n", ans[i]);
    }

    return 0;
}