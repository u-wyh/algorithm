// https://www.luogu.com.cn/problem/P1537
// 题意：给价值为 1 至 6 的弹珠分别有多少个，判断能不能把所有弹珠分成总价值相同的两份。每组先按题面格式输出组编号，再输出是否可分，组后留一个空行。
// 数据范围：各类数量非负，弹珠总数不超过 20000，六个 0 结束输入。

#include<stdio.h>
#include<limits.h>
#define Max 20005

int nums[Max];

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int k=0;
    int a,b,c,d,e,f;
    while(scanf("%d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)==6&&(a+b+c+d+e+f)!=0)
    {
        int sum=0;
        k++;
        printf("Collection #%d:\n",k);
        sum=a+b*2+c*3+d*4+e*5+f*6;
        int h=a+b+c+d+e+f;
        if(sum%2==1)
        {
            printf("Can't be divided.\n");
            printf("\n");
            continue;
            //return 0;
        }
        int i=1;
        while(a)
        {
            nums[i++]=1;
            a--;
        }
        while(b)
        {
            nums[i++]=2;
            b--;
        }
        while(c)
        {
            nums[i++]=3;
            c--;
        }
        while(d)
        {
            nums[i++]=4;
            d--;
        }
        while(e)
        {
            nums[i++]=5;
            e--;
        }
        while(f)
        {
            nums[i++]=6;
            f--;
        }
        int dp[h+1][sum+1];
        for(int i=0;i<=h;i++)
        {
            for(int j=0;j<=sum;j++)
            {
                dp[i][j]=INT_MIN;
            }
        }
        dp[0][0]=0;
        for(int i=1;i<=h;i++)
        {
            for(int j=0;j<=sum;j++)
            {
                dp[i][j]=max(dp[i][j],dp[i-1][j+nums[i]]);
                if(j>=nums[i])
                    dp[i][j]=max(dp[i][j],dp[i-1][j-nums[i]]+nums[i]);
                else
                    dp[i][j]=max(dp[i][j],dp[i-1][nums[i]-j]+j);
            }
        }
        if(dp[h][0]>0)
        {
            printf("Can be divided.\n");
            printf("\n");
            continue;
            //return 0;
        }
        else
        {
            printf("Can't be divided.\n");
            printf("\n");
            continue;
            //return 0;
        }
    }
    return 0;
}
