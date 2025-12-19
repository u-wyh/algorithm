#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 2, M = 320;
int a[M][N];
map<pair<int, int>, int> mp;
int n, m, q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m >> q;
    int sz = m / M + 1;
    
    // 初始化每个块的映射数组
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= sz; j++) {
            a[j][i] = i;
        }
    }
    
    while (q--) {
        int op;
        cin >> op;
        
        if (op == 1) {
            int u, v;
            cin >> u >> v;
            v--;  // 转换为0-indexed
            
            // 记录桥梁
            mp[{u, v}] = u + 1;
            mp[{u + 1, v}] = u;
            
            int x = u, y = u + 1;
            int block_idx = v / M;
            
            // 从当前层向前处理到当前块的起始层
            for (int i = v - 1; i >= block_idx * M; i--) {
                if (mp.find({x, i}) != mp.end()) {
                    x = mp[{x, i}];
                }
                if (mp.find({y, i}) != mp.end()) {
                    y = mp[{y, i}];
                }
            }
            
            // 交换当前块中两个国家的映射
            swap(a[block_idx][x], a[block_idx][y]);
        } else {
            int u;
            cin >> u;
            
            // 依次通过所有块
            for (int i = 0; i <= sz; i++) {
                u = a[i][u];
            }
            cout << u << "\n";
        }
    }
    
    return 0;
}