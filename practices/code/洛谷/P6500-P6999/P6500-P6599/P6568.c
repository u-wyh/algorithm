// https://www.luogu.com.cn/problem/P6568
// 题意：n 个无限大水壶初始水量 A_i，
// 可进行不超过 k 次操作将 x 号水壶的水全倒入 x+1
// 号水壶（1 <= x <= n-1）
// 最后任选一个水壶喝掉所有水，求最多能喝到的水量。
// 数据范围：1 <= n <= 10^6，0 <= k <= n-1，
// 0 <= A_i <= 10^3。
// 算法标签：滑动窗口
#include<stdio.h>

int max(int a,int b){
    return a>b?a:b;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int nums[n+2],sum[n+1],ans=0;
    nums[n+1]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        if(i<=k+1){
            sum[k]+=nums[i];
            ans=max(ans,sum[k]+nums[i+1]);
        }else{
            sum[i]=sum[i-1]+nums[i]-nums[i-k];
            ans=max(ans,sum[i]+nums[i+1]);
        }
    }
    printf("%d\n",ans);
    return 0;
}
