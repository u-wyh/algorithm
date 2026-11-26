// https://www.luogu.com.cn/problem/P1509
// 题意：每项任务各消耗预算、点数和时间。给预算 m、点数 r，任选任务使两类消耗均不超限，先让任务数量最大，再让总时间最小。输出最小时间，一项也做不了时输出 0。
// 数据范围：1 ≤ n,m,r ≤ 100，单任务预算及点数消耗在 [1,100]，耗时在 [1,1000]。

#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int rmb[n+1],rp[m+1],time[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&rmb[i],&rp[i],&time[i]);
    }
    int RMB,RP;
    scanf("%d %d",&RMB,&RP);
    return 0;
}
