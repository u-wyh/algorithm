#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;  // 定义模数
const int MAXN = 100005;     // 最大可能n值

int n;           // 农场大小
int y[MAXN];     // y[i]表示第i行喷头所在的列
int l[MAXN], r[MAXN]; // l[i]表示前i行喷头列的最小值，r[i]表示后i行喷头列的最大值
int up[MAXN];    // up[j]表示列j能被覆盖的最小行号
long long sum1[MAXN], sum2[MAXN]; // 前缀和数组：sum1是up的前缀和，sum2是j*up[j]的前缀和

int main() {
    // 读取输入
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a++; b++;  // 将坐标从0-indexed转换为1-indexed
        y[a] = b;  // 记录第a行喷头所在的列
    }
    
    // 计算l数组：l[i]表示前i行喷头列的最小值
    l[0] = MAXN;  // 初始化边界值
    for (int i = 1; i <= n; i++) {
        l[i] = min(l[i-1], y[i]);  // 递推计算最小值
    }
    
    // 计算r数组：r[i]表示从第i行到最后一行喷头列的最大值
    r[n+1] = 0;  // 初始化边界值
    for (int i = n; i >= 1; i--) {
        r[i] = max(r[i+1], y[i]);  // 递推计算最大值
    }
    
    // 计算up数组：up[j]表示列j能被覆盖的最小行号
    int pos = r[1];  // 从最大列开始
    for (int i = 1; i <= n; i++) {
        // 对于每一行i，找到所有满足l[i] <= j <= r[1]的列j
        while (pos >= 1 && pos >= l[i]) {
            up[pos] = i;  // 记录列pos能被覆盖的最小行号是i
            pos--;        // 处理下一列
        }
    }
    
    // 计算前缀和数组
    for (int j = 1; j <= n; j++) {
        sum1[j] = (sum1[j-1] + up[j]) % MOD;                  // up数组的前缀和
        sum2[j] = (sum2[j-1] + 1LL * j * up[j]) % MOD;        // j*up[j]的前缀和
    }
    
    // 计算答案
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        // 计算当前行i的有效列范围长度
        long long len = r[i] - l[i];
        if (len < 0) continue;  // 如果无效则跳过
        
        // 第一项：基本贡献项
        long long term1 = (len * (len + 1) / 2) % MOD;  // 等差数列求和公式
        term1 = term1 * i % MOD;                        // 乘以行号i
        
        // 计算需要的前缀和区间
        int r_idx = r[i] - 1;  // 右边界索引
        int l_idx = l[i] - 1;  // 左边界索引
        
        // 计算区间和，注意处理负数模
        long long s1 = (sum1[r_idx] - sum1[l_idx] + MOD) % MOD;
        long long s2 = (sum2[r_idx] - sum2[l_idx] + MOD) % MOD;
        
        // 第二项和第三项：调整项
        long long term2 = r[i] * s1 % MOD;  // 使用前缀和计算的项
        long long term3 = s2;               // 使用加权前缀和计算的项
        
        // 累加当前行的贡献到总答案
        ans = (ans + term1 - term2 + term3 + MOD) % MOD;
    }
    
    // 输出结果
    printf("%lld\n", ans);
    return 0;
}