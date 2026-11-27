// https://www.luogu.com.cn/problem/P5639
// 题意：一条路上有 n 个排成直线的监控，每个监控每秒在开（1）与关（0）间切换；小 Z 每次可用 1 秒连续穿过任意多个关闭的监控，求安全通过的最短时间。
// 输入 n 及第 0 秒各监控的开关状态（保证第 1 个为 0）；输出最短通过时间。
// 数据范围：1 <= n <= 10^6。
// 算法标签：贪心、模拟
#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int ans=0,nums[n+1];
    nums[0]=-1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        if(nums[i]!=nums[i-1])
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}
