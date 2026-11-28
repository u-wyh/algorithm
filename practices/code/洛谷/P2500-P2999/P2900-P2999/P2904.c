// https://www.luogu.com.cn/problem/P2904
// 题意：输入奶牛数 N、约翰独自划船单程过河耗时 M，
// 以及木筏上增加第 i 头牛额外增加的耗时 M_i。
// 约翰必须一直在木筏上；
// 载 k 头牛过河耗时为 M + sum_{i=1..k} M_i 分钟，
// 约翰独自划船返回耗时为 M 分钟。
// 合理规划分批渡河方式，将所有 N 头牛运到对岸。
// 输出一行一个整数，表示让所有奶牛过河的最短总时间。
// 数据范围：对于 100% 的数据，1 <= N <= 2500，
// 1 <= M <= 1000，1 <= M_i <= 1000。
// 难度评分：1300（洛谷分级换算）
// 算法标签：动态规划、完全背包、前缀和
#include<stdio.h>
#include<limits.h>
#define N 2501

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    int sum[n+1];
    sum[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum[i]=sum[i-1]+nums[i];
    }
    for(int i=1;i<=n;i++)
        sum[i]+=2*m;
    int f[n+1];
    f[0]=0;
    for(int i=1;i<=n;i++)
        f[i]=INT_MAX;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (f[j - i] != INT_MAX) { // 确保f[j-i]不是无限大才进行更新
                f[j] = min(f[j] , f[j - i] + sum[i]); // 更新f[j]
            }
        }
    }
    printf("%d\n",f[n]-m);
    return 0;
}
