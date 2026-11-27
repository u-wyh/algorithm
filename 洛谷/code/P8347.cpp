// https://www.luogu.com.cn/problem/P8347
// 题意：T 组数据，给定 n 个节点的树（n >= 2），Hifuu 先手与 Luna 交替操作。
// 每回合操作者选择一个节点，删去该节点及其相连的所有边，再从分裂出的若干连通块中保留一个。
// 若回合结束后只剩 1 个节点，则该回合操作者失败。
// 求谁必胜（输出 Hifuu 或 Luna）。
// 数据范围：100% 数据满足 1 <= T <= 5，2 <= n <= 10^5。
// 算法标签：博弈论、树论
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 100005;
int degree[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    
    // 初始化度数数组
    for (int i = 1; i <= n; i++) {
        degree[i] = 0;
    }
    
    // 读入边并统计度数
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        degree[u]++;
        degree[v]++;
    }
    
    // 检查是否存在度数为偶数的节点
    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2 == 0) {
            printf("Hifuu\n");
            return;
        }
    }
    
    // 所有节点度数都是奇数
    printf("Luna\n");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}