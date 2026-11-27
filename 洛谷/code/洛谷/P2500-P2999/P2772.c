// https://www.luogu.com.cn/problem/P2772
// 题意：平面上 n 个互异整点，
// 若不存在另一点 (x,y) 满足 x >= a 且 y >= b，
// 则 (a,b) 为极大点。
// 按 x 坐标从小到大输出所有极大点，
// 格式为 (x1,y1),(x2,y2),...。
// 数据范围：1 <= n <= 5*10^5，0 <= x, y <= 10^5。
// 算法标签：排序、贪心
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b,c;
}point;

int cmp(const void *a,const void *b)
{
    point *pa=(point *)a;
    point *pb=(point *)b;

    if(pa->a > pb->a)
        return -1;
    if(pa->a < pb->a)
        return 1;
    return pb->b - pa->b;
}

int main()
{
    int n;
    scanf("%d",&n);
    point nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&nums[i].a,&nums[i].b);
        nums[i].c=0;
    }
    qsort(nums+1,n,sizeof(point),cmp);
    /*
    for(int i=1;i<=n;i++)
    {
        printf("%d %d\n",nums[i].a,nums[i].b);
    }
    */
    nums[1].c=1;
    int B=nums[1].b;
    for(int i=2;i<=n;i++)
    {
        if(nums[i].a!=nums[i-1].a)
        {
            if(nums[i].b>B)
            {
                B=nums[i].b;
                nums[i].c=1;
            }
        }
    }
    for(int i=n,k=0;i>=1;i--)
    {
        if(nums[i].c==1&&k==0)
        {
            printf("(%d,%d)",nums[i].a,nums[i].b);
            k++;
        }
        else if(nums[i].c==1)
        {
            printf(",(%d,%d)",nums[i].a,nums[i].b);
        }
    }
    return 0;
}
