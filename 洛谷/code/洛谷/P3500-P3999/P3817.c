// https://www.luogu.com.cn/problem/P3817
// 题意：第一行输入糖果盒数 n 和上限 x，
// 第二行输入 n 个整数 a_1..a_n 表示每盒的糖果数。
// 每次可从任一盒吃掉一颗糖，使任意两个相邻盒子的糖果数之和都不超过 x。
// 输出最少需要吃掉的糖果总数。
// 数据范围：对于 100% 的数据，2 <= n <= 10^5，
// 0 <= a_i, x <= 10^9。
// 算法标签：贪心
#include<stdio.h>

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    nums[0]=0;
    long long ans=0;
    for(int i=0;i<n;i++){
        if((nums[i]+nums[i+1])>m)
        {
            ans+=(nums[i]+nums[i+1]-m);
            nums[i+1]=m-nums[i];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
