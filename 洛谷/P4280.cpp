#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;
const int MAXM = 105;

int n, m;
int a[MAXN];
int lis[2][MAXM];
long long ans;

int main() {
    scanf("%d%d", &n, &m);
    
    // 输入并统计初始后缀和
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if (a[i] != -1) {
            ++lis[1][a[i]];
        }
    }
    
    // 计算后缀和
    for (int i = 1; i <= m; ++i) {
        lis[1][i] += lis[1][i - 1];//对于第0个位置而言 后面表示小于等于i的元素个数
    }
    
    // 处理每个元素
    for (int i = 1; i <= n; ++i) {
        if (a[i] == -1) {
            // 寻找最优的填充值
            int ct = 0, mx = 0x7fffffff;
            for (int j = 1; j <= m; ++j) {
                int current = lis[0][j + 1] + lis[1][j - 1];
                if (current < mx) {
                    mx = current;
                    ct = j;
                }
            }
            a[i] = ct;
        } else {
            // 更新后缀和
            for (int j = a[i]; j <= m; ++j) {
                --lis[1][j];//表示对于剩下的位置而言  数字小于等于j的个数减少一
            }
        }
        
        // 统计逆序对并更新前缀和
        ans += lis[0][a[i] + 1];//统计前面大于自己的元素的个数
        for (int j = 1; j <= a[i]; ++j) {
            ++lis[0][j];//表示对于后面的元素而言 如果你的数字是j  那么大于你的数字个数加一
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}