// https://www.luogu.com.cn/problem/P1537
// 题意：给价值为 1 至 6 的弹珠分别有多少个，
// 判断能不能把所有弹珠分成总价值相同的两份。
// 每组先按题面格式输出组编号，再输出是否可分，组后留一个空行。
// 数据范围：各类数量非负，弹珠总数不超过 20000，六个 0 结束输入。
// 难度评分：1500（洛谷分级换算）
// 算法标签：多重背包、动态规划

#include<stdio.h>

int main()
{
    int k=0;
    int num[7];
    while(scanf("%d %d %d %d %d %d",&num[1],&num[2],&num[3],&num[4],&num[5],&num[6])==6
          &&(num[1]+num[2]+num[3]+num[4]+num[5]+num[6])!=0)
    {
        int sum=0;
        k++;
        printf("Collection #%d:\n",k);
        sum=num[1]+num[2]*2+num[3]*3+num[4]*4+num[5]*5+num[6]*6;
        int h=(num[1]+num[2]+num[3]+num[4]+num[5]+num[6]);
        if(sum%2==1)
        {
            printf("Can't be divided.\n");
            printf("\n");
            continue;
        }
        int dp[sum/2+1];
        for(int i=0;i<=sum/2;i++)
        {
            dp[i]=0;
        }
        dp[0]=1;
        for(int i=1;i<=6;i++)
        {
            for(int j=sum/2;j>=1;j--)
            {
                for(int k=1;k<=num[i]&&j>=k*i;k++)
                    dp[j]|=dp[j-k*i];
            }
        }
        if(dp[sum/2])
        {
            printf("Can be divided.\n");
            printf("\n");
            continue;
        }
        else
        {
            printf("Can't be divided.\n");
            printf("\n");
            continue;
        }
    }
    return 0;
}
