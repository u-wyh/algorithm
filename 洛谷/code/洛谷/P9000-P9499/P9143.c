// https://www.luogu.com.cn/problem/P9143
// 题意：给定 [1, n] 内每个整数 i 的数量 a_i，
// 总数为 S = sum a_i。
// 定义序列众数 maj 为出现次数最多的数（并列取最大者）。
// 将这 S 个数重排为 b_1..b_S，
// 最大化 sum_{i=1}^S maj(b_1..b_i) 并输出该最大值。
// 数据范围：1 <= n <= 10^5，1 <= a_i <= 10^5。
// 算法标签：贪心、模拟
#include<stdio.h>
#include<stdlib.h>

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    long long ans=0;
    for(int i=n;i>=1;i--){
        int k=0,m=nums[i];
        if(m==0)
            continue;
        for(int j=i;j>=1;j--){
            if(nums[j]==0)
                continue;
            k+=min(m,nums[j]);
            if(nums[j]<=m)
                nums[j]=0;
            else
                nums[j]-=m;
        }
        ans+=k*i;
    }
    printf("%lld\n",ans);
    return 0;
}
