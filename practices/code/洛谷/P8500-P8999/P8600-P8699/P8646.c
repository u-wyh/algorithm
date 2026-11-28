// https://www.luogu.com.cn/problem/P8646
// 题意：输入整数 N 和 N 个正整数 A_1..A_N（每种有无限个），
// 输出有多少个正整数不能由这些数非负整数线性组合凑出；
// 若凑不出的数目有无限多个，输出 INF。
// 数据范围：1 <= N <= 100，1 <= A_i <= 100。
// 难度评分：1300（洛谷分级换算）
// 算法标签：动态规划、最大公约数
#include<stdio.h>

int gcd(int a, int b)
{
    if(b == 0)  return a;
    else    return gcd(b, a%b);
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int GCD=nums[1];
    for(int i=2;i<=n;i++)
        GCD=gcd(GCD,nums[i]);
    if(GCD!=1)
    {
        printf("INF\n");
        return 0;
    }
    int dp[1000105];
    for(int i=0;i<=1000104;i++)
        dp[i]=0;
    dp[0]=1;
    for(int i=0;i<=1000000;i++)
		if(dp[i])
		for(int j=1;j<=n;j++)
			dp[i+nums[j]]=1;
	int count=0;
    for(int i=1;i<=1000000;i++)
        if(!dp[i])
            count++;
    printf("%d\n",count);
    return 0;
}
