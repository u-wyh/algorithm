// https://www.luogu.com.cn/problem/P5602
// 题意：有 n 种美食各有美味值 a_i，任选一个非空子集吃下，舒适度定义为总美味值的平方除以所吃美食种数，求最大舒适度。
// 输入 n 及数组 a；输出最大舒适度（相对或绝对误差不超过 10^-6 即正确）。
// 数据范围：1 <= n <= 3*10^5，1 <= a_i <= 10^6。
#include<stdio.h>
#include<stdlib.h>
// 算法标签：贪心、排序

int cmp(const void *a,const void *b)
{
    return (*(long long *)b-*(long long *)a);
}

int main()
{
    int n;
    scanf("%d",&n);
    long long a[n+1],sum=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
    }
    qsort(a+1,n,sizeof(long long),cmp);
    double ans=0.0;
    for(int i=1;i<=n;i++)
    {
        if(1.0*(sum+a[i])/i*(sum+a[i])>ans)
        {
            ans=1.0*(sum+a[i])/i*(sum+a[i]);
            sum+=a[i];
        }
        else
            break;
    }
    printf("%.6lf\n",ans);
    return 0;
}
