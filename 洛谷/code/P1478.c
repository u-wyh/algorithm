// https://www.luogu.com.cn/problem/P1478
// 题意：有 n 个苹果，第 i 个高度 x[i]，摘下花费 y[i] 点力气。站到椅子上后最高够到 a+b，力气预算是 s。求能摘下的最多苹果数。
// 数据范围：n ≤ 5000，a ≤ 50，b ≤ 200，s ≤ 1000，x[i] ≤ 280，y[i] ≤ 100。
// 算法标签：贪心、排序

#include<stdlib.h>
#include<stdio.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n,m,x,y;
    scanf("%d %d %d %d",&n,&m,&x,&y);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
        if(a[i]>x+y)
            b[i]=1e9;
    }
    qsort(b+1,n,sizeof(int),cmp);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(m>=b[i])
        {
            ans++;
            m-=b[i];
        }
        else
            break;
    }
    printf("%d\n",ans);
    return 0;
}
