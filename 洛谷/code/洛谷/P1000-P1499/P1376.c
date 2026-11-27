// https://www.luogu.com.cn/problem/P1376
// 题意：工厂共工作 N 周，第 i 周每生产一台机器耗费 C[i]，
// 必须交付 Y[i] 台。
// 交付可以使用当周生产的机器或旧库存，每台库存每跨过一周另付 S。
// 求满足全部订单的最小费用。
// 数据范围：1 ≤ N ≤ 10000，1 ≤ C[i] ≤ 5000，
// 1 ≤ S ≤ 100，0 ≤ Y[i] ≤ 10000。
// 算法标签：贪心

#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[n+1];
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
        if(i!=1)
        {
            if(a[i]>a[i-1]+m)
                a[i]=a[i-1]+m;
        }
        ans+=a[i]*b[i];
    }
    printf("%lld\n",ans);
    return 0;
}
