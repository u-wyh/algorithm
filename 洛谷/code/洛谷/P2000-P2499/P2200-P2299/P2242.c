// https://www.luogu.com.cn/problem/P2242
// 题意：直线上有 n 个从小到大互异的坑，用 m 段闭区间覆盖所有坑。
// 求这 m 段区间的最小总长度。
// 输出最小总长度。
// 数据范围：2 <= m <= n <= 15000，坐标在长整范围内。
// 算法标签：贪心、排序
#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(i==1)
            b[i]=0;
        else
            b[i]=a[i]-a[i-1];
    }
    qsort(b+1,n,sizeof(int),cmp);
    int ans=(a[n]-a[1]+1);
    //printf("%d\n",ans);
    for(int i=1;i<=m-1;i++)
    {
        ans-=b[i];
    }
    //printf("%d\n",ans);
    ans+=(m-1);
    printf("%d\n",ans);
    return 0;
}
