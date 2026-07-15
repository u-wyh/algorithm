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