// https://www.luogu.com.cn/problem/P8548
// 题意：共 n 株花，第 i 株价格 cost_i、新鲜度 fr_i、美丽度 be_i。
// q 次独立询问每次给出预算上限 c_j 与新鲜度下限 f_j，在总价 <= c_j 且总新鲜度 >= f_j 的前提下最大化总美丽度，无解输出 0。
// 数据范围：100% 数据满足 3 <= n <= 500，1 <= q <= 10^6
// 0 <= cost_i, fr_i, c_j, f_j <= 500，1 <= be_i <= 10^6。
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[n+1],c[n+1];
    int sum1=0,sum2=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&a[i],&b[i],&c[i]);
        sum1+=a[i];
        sum2+=b[i];
    }
    return 0;
}
