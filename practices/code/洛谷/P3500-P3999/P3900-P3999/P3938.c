// https://www.luogu.com.cn/problem/P3938
// 题意：兔子按斐波那契模型繁衍
// （每对兔子从出生后第二个月起
// 每月月初生一对新兔子，按出生顺序编号，
// 同月出生则父母编号小的优先编号，
// 1 号兔子为祖先）。
// 给出 m 组询问 (a_i, b_i)，
// 求编号为 a_i 和 b_i 的两对兔子的最近公共祖先编号。
// 数据范围：
// 测试点 10 中 m = 300010（各测试点 m 最大为 300010），
// a_i, b_i <= 10^12。
// 难度评分：1300（洛谷分级换算）
// 算法标签：贪心、排序
#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}

int main()
{
    int k;
    scanf("%d",&k);
    for(int i=1;i<=k;i++)
    {
        int n,m,t;
        scanf("%d %d %d",&n,&t,&m);
        int defence[n+1],a;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&defence[i]);
        }
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&a);
            defence[a]-=2;
        }
        qsort(defence+1,n,sizeof(int),cmp);
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            if(defence[i]>0)
                ans++;
            else
            {
                if(t+defence[i]>=1)
                {
                    t+=defence[i]-1;
                    ans++;
                }
                else
                    break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
