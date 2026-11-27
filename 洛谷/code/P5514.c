// https://www.luogu.com.cn/problem/P5514
// 题意：将 n 个非负整数划分为若干个非空组，每组权值为组内所有数的异或和，求所有组权值和的最小值。
// 输入 n 及 n 个非负整数 a_i；输出最小的分组权值和。
// 数据范围：n <= 10^6，0 <= a_i <= 10^9。
#include<stdio.h>
// 算法标签：位运算、贪心

int main()
{
    int n,ans;
    scanf("%d %d",&n,&ans);
    int a;
    for(int i=2;i<=n;i++){
        scanf("%d",&a);
        ans^=a;
    }
    printf("%d\n",ans);
    return 0;
}
