// https://www.luogu.com.cn/problem/P10771
// 题意：有 n 个学生，第 i 人物理成绩为 A[i]、生物成绩为 B[i]。恰好选 a 人参加物理、b 人参加生物，每人只参加一项。求所选对应成绩的最大总和。
// 数据范围：1 ≤ n ≤ 10^5，0 ≤ a,b ≤ n，a+b=n，0 ≤ A[i],B[i] ≤ 10^4。

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b,c;
}score;

int cmp(const void *a,const void *b)
{
    score *sa=(score *)a;
    score *sb=(score *)b;
    return sa->c - sb->c;
}

int main()
{
    int n,x,y;
    scanf("%d %d %d",&n,&x,&y);
    score nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i].a);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i].b);
        nums[i].c=nums[i].a-nums[i].b;
    }
    qsort(nums+1,n,sizeof(score),cmp);
    //printf("%d\n",nums[1].c);
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        if(i<=y)
            ans+=nums[i].b;
        else
            ans+=nums[i].a;
        //printf("%lld\n",ans);
    }
    printf("%lld\n",ans);
    return 0;
}
