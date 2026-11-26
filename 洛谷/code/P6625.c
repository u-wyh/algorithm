// https://www.luogu.com.cn/problem/P6625
// 题意：一排 n 张卡牌分值为 a_i，每次可选最左侧至少 2 张连续卡牌替换为一张新卡牌放到最左端，新分值为所选卡牌之和并加到总分；可随时结束游戏，求最高总分。
// 数据范围：1 <= n <= 10^5，|a_i| <= 10^5。
#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1],sum[n+1];
    sum[0]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum[i]=a[i]+sum[i-1];
    }
    long long  ans=0;
    for(int i=2;i<=n;i++){
        if(sum[i]>0)
            ans+=sum[i];
    }
    printf("%lld\n",ans);
    return 0;
}

