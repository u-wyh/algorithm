// https://www.luogu.com.cn/problem/P1230
// 题意：初始奖励 m 元，共 n 个时段和 n 个小游戏（每个需占 1 个整时段完成）。
// 题意：游戏 i 需在期限 t_i 前完成，否则从奖金中扣除 w_i 元（不会扣成负值赔钱）。
// 题意：合理安排做游戏的顺序，求能赢取的最大金额。
// 输入：第一行 m，第二行 n，第三行 n 个数表期限 t_i，第四行 n 个数表扣款 w_i。
// 输出：一行输出能赢取的最多的钱。
// 数据范围：1 <= n <= 500，1 <= m <= 5 * 10^5。
// 数据范围：1 <= t_i <= n，1 <= w_i <= 1000。
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}game;

int cmp(const void *a,const void *b)
{
    game * ga=(game *)a;
    game * gb=(game *)b;

    /*if(ga->a > gb->a)
        return 1;
    if(ga->a < gb->a)
        return -1;*/

    return gb->b - ga->b;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    game nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i].a);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i].b);
        m-=nums[i].b;
    }
    qsort(nums+1,n,sizeof(game),cmp);

    for(int i=1;i<=n;i++)
    {
        printf("%d %d\n",nums[i].a,nums[i].b);
    }

    int k=1;
    for(int i=1;i<=n;i++)
    {
        if(k<=nums[i].a)
        {
            k++;
            m+=nums[i].b;
        }
    }
    printf("%d\n",m);
    return 0;
}
