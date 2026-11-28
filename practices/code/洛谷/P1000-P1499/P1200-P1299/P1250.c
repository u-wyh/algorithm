// https://www.luogu.com.cn/problem/P1250
// 题意：路边有编号 1..n 的地区，每个地区最多可种 1 棵树。
// 题意：共有 h 个要求，
// 第 i 个要求在区间 [b_i, e_i] 内至少种 t_i 棵树，
// 求最少总树数。
// 输入：第一行 n，第二行 h，
// 接下来 h 行每行输入 b_i, e_i, t_i。
// 输出：一行输出满足所有要求的最少种树数量。
// 数据范围：1 <= n <= 3 * 10^4，
// 1 <= h <= 5 * 10^3。
// 数据范围：1 <= b_i <= e_i <= n，
// 1 <= t_i <= e_i - b_i + 1。
// 难度评分：1200（洛谷分级换算）
// 算法标签：贪心、排序
#include<stdio.h>
#include<stdlib.h>
#define MAX 30000+4

int used[MAX];

typedef struct
{
    int a,b,c;
}tree;

int cmp(const void *a,const void *b)
{
    tree * ta=(tree *)a;
    tree * tb=(tree *)b;

    if(ta->b < tb->b)
        return -1;
    if(ta->b > tb->b)
        return 1;

    return tb->b-ta->b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    tree nums[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d %d",&nums[i].a,&nums[i].b,&nums[i].c);
    }
    qsort(nums+1,m,sizeof(tree),cmp);
    /*
    printf("-----------------------------\n");
    for(int i=1;i<=m;i++)
    {
        printf("%d %d %d\n",nums[i].a,nums[i].b,nums[i].c);
    }
    printf("-----------------------------\n");
    */
    for(int i=nums[1].b,j=1;j<=nums[1].c;j++,i--)
    {
        used[i]=1;
    }
    for(int i=2;i<=m;i++)
    {
        int count=0;
        for(int j=nums[i].a;j<=nums[i].b;j++)
        {
            if(used[j]==1)
                count++;
        }
        //printf("%d\n",count);
        if(count>=nums[i].c)
            continue;
        else
        {
            for(int j=nums[i].b,k=1;k<=nums[i].c-count;j--)
            {
                if(used[j]==0)
                {
                    used[j]=1;
                    k++;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=used[i];
    }
    printf("%d\n",ans);
    return 0;
}
