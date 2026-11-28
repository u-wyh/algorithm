// https://www.luogu.com.cn/problem/P9344
// 题意：多组数据（共 T 组）。
// 每组有 n 块地板，第 i 块积灰程度为 a_i，
// 类别为 c_i ∈ {0, 1}。
// 每次可选两个未清理过的下标 i <= j 且 c_i = c_j
// 花费 a_i + a_j 能量清理 [i, j]
// 内所有地板（注意即使中间有已清理地板
// 也只要求端点 i, j 未被清理过，
// i = j 时花费 2a_i）。
// 求清理全部地板的最小总能量。
// 题意：第一行输入 T，每组输入 n、a_1..a_n、c_1..c_n；
// 输出 T 行最小能量。
// 数据范围：1 <= T <= 10^5，
// 1 <= n, sum(n) <= 2 * 10^6，c_i ∈ {0, 1}，
// 1 <= a_i <= 10^9。
// 难度评分：1200（洛谷分级换算）
// 算法标签：贪心、枚举
#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        long long a[n+1];
        int c[n+1];
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&c[i]);
        }
        if(c[1]==c[n]){
            printf("%lld\n",a[1]+a[n]);
            continue;
        }
        long long ans=4000000000;
        for(int i=1;i<n;i++){
            if(c[i]==c[1]&&c[i+1]==c[n]){
                ans=ans<(a[i]+a[1]+a[i+1]+a[n])?ans:(a[i]+a[1]+a[i+1]+a[n]);
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
