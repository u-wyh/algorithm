// https://www.luogu.com.cn/problem/P2616
// 题意：数轴 [0,E] 上有 N 家商店（可同坐标），第 i 家在 X_i，
// 售价 C_i/吨，库存 F_i 吨。
// 载 X 吨走 D 公里花费 D*X 元，从 0 走到 E 需买到 K 吨饲料，
// 求最小总花费。
// 输出最小总花费。
// 数据范围：1 <= K, N <= 100，1 <= E <= 350，
// 0 < X_i < E，1 <= F_i <= 100
// 1 <= C_i <= 10^6。
// 算法标签：贪心、排序
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b,e;
}shop;

int cmp(const void *a,const void *b)
{
    shop * sa=(shop *)a;
    shop * sb=(shop *)b;
    return sa->b-sb->b;
}
int main()
{
    int m,k,n;
    scanf("%d %d %d",&m,&k,&n);
    shop nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&nums[i].e,&nums[i].a,&nums[i].b);
        nums[i].b+=k-nums[i].e;
    }
    qsort(nums+1,n,sizeof(shop),cmp);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(m>0)
        {
            if(m>=nums[i].a)
            {
                ans+=nums[i].b*nums[i].a;
                m-=nums[i].a;
            }
            else
            {
                ans+=m*nums[i].b;
                m=0;
            }
        }
        else
            break;
    }
    printf("%d\n",ans);
    return 0;
}
