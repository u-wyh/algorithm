// https://www.luogu.com.cn/problem/P2089
// 题意：10 种配料，每种质量只能取 1、2 或 3 克。
// 给定总美味程度 n，求所有总质量恰好为 n 的配料方案。
// 先输出方案总数，再按字典序输出所有具体方案；若无解则输出 0。
// 数据范围：
// 1 <= n <= 10000（有解范围为 10 <= n <= 30）。
// 难度评分：900（洛谷分级换算）
// 算法标签：枚举
#include<stdio.h>

#define FOR(i,n,m) for(int i=n;i<=m;i++)

int main()
{
    int n,ans=0;
    scanf("%d",&n);
    FOR(a,1,3) FOR(b,1,3) FOR(c,1,3) FOR(d,1,3) FOR(e,1,3)
    FOR(f,1,3) FOR(g,1,3) FOR(h,1,3) FOR(i,1,3) FOR(j,1,3)
    if(a+b+c+d+e+f+g+h+i+j==n)
        ans++;
    printf("%d\n",ans);
    FOR(a,1,3) FOR(b,1,3) FOR(c,1,3) FOR(d,1,3) FOR(e,1,3)
    FOR(f,1,3) FOR(g,1,3) FOR(h,1,3) FOR(i,1,3) FOR(j,1,3)
    if(a+b+c+d+e+f+g+h+i+j==n)
        printf("%d %d %d %d %d %d %d %d %d %d\n",a,b,c,d,e,f,g,h,i,j);
    return 0;
}
