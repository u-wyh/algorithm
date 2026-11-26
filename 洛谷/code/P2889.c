// https://www.luogu.com.cn/problem/P2889
// 题意：输入总小时数 N、可挤奶时间段数 M、挤奶后必需休息时间 R，以及 M 个时间段 [Start_i, End_i] 及其产奶量 Eff_i。
// 每次选定一个时间段挤奶并获得 Eff_i 牛奶后，需休息 R 小时才能开始下一段挤奶（下段开始时间不早于本段结束时间 + R）。
// 挑选互不冲突的挤奶时间段，使总产奶量最大。
// 输出一行一个整数，表示最大总产奶量。
// 数据范围：对于全部测试点，1 <= N <= 10^6，1 <= M <= 10^3，1 <= Eff_i <= 10^6
// 0 <= Start_i < End_i <= N。
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int m,n,r;
    scanf("%d %d %d",&m,&n,&r);
    int start[n+1],end[n+1],eff[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&start[i],&end[i],&eff[i]);
        end[i]+=r;
    }

    return 0;
}
