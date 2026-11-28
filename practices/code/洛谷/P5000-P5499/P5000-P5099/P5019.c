// https://www.luogu.com.cn/problem/P5019
// 题意：长为 n 的道路初始各位置下陷深度为 d_i，
// 每天可将一段当前深度均非 0 的连续区间整体减 1，
// 求把所有位置深度清零的最少天数。
// 数据范围：1 <= n <= 100000，0 <= d_i <= 10000。
// 难度评分：1200（洛谷分级换算）
// 算法标签：贪心、差分
#include<stdio.h>

#define MAX 100000+5

int max(int a,int b){
    return a>b?a:b;
}

int n;
int nums[MAX];

int main()
{
    long long ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        ans+=max(0,nums[i]-nums[i-1]);
    }
    printf("%lld\n",ans);
    return 0;
}
