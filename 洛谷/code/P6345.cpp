#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXV = 25005; // 最大可能积水总量

int n;
int h[MAXN];
bitset<MAXV> dp; // dp[i]表示能否得到积水总量i

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    
    // 将柱子按高度升序排序
    sort(h + 1, h + n + 1);
    
    dp[0] = 1; // 初始状态：0积水是可能的
    
    // 对于每个柱子j，考虑所有比它高的柱子st
    for (int j = 1; j < n; j++) {
        bitset<MAXV> temp;
        
        // 对于每个比j高的柱子st
        for (int st = j + 1; st < n; st++) {
            int water = h[st] - h[j]; // 可能产生的积水高度
            if (water > 0) {
                temp |= (dp << water); // 将dp左移water位，表示增加water单位的积水
            }
        }
        
        dp |= temp; // 更新dp
    }
    
    // 输出所有可能的积水总量
    bool first = true;
    for (int i = 0; i < MAXV; i++) {
        if (dp[i]) {
            if (!first) cout << " ";
            cout << i;
            first = false;
        }
    }
    cout << endl;
    
    return 0;
}