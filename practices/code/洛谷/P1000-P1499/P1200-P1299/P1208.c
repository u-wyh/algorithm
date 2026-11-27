// https://www.luogu.com.cn/problem/P1208
// 题意：需要采购总量为 n 的牛奶，共有 m 个奶农，
// 第 i 个单价 p_i 且最多供应 a_i。
// 题意：每天从每位奶农购买的整数数量不超过其产量，保证总产量不少于 n。
// 输入：第一行输入 n, m，接下来 m 行每行输入 p_i, a_i。
// 输出：一行输出采购 n 单位牛奶的最小总费用。
// 数据范围：0 <= n, a_i <= 2 * 10^6。
// 数据范围：0 <= m <= 5000，0 <= p_i <= 1000。
// 算法标签：贪心、排序
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}milk;

int cmp(const void *a,const void *b)
{
    milk *ma=(milk *)a;
    milk *mb=(milk *)b;
    return ma->a-mb->a;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    milk nums[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,m,sizeof(milk),cmp);
    //printf("%d %d\n",nums[1].a,nums[1].b);
    long long  ans=0;
    for(int i=1;i<=m;i++)
    {
        if(n>0)
        {
            if(n>nums[i].b)
            {
                n-=nums[i].b;
                ans+=nums[i].b*nums[i].a;
            }
            else
            {
                ans+=n*nums[i].a;
                n=0;
            }
        }
        else
            break;
    }
    printf("%lld\n",ans);
    return 0;
}
