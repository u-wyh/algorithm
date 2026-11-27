// https://www.luogu.com.cn/problem/P1182
// 题意：给 N 个数，把数组切成恰好 M 个连续非空段。对每种切法找出段和最大的那一段，求这个最大段和能降到多少。
// 数据范围：1 ≤ M ≤ N ≤ 10^5，0 ≤ A[i] < 10^8，答案不超过 10^9。
// 算法标签：二分答案、贪心

#include<stdio.h>
#include<limits.h>

long long check(long long limit,long long *nums,int n){
    long long ans=1,sum=0;
    for(int i=1;i<=n;i++){
        if(nums[i]>limit){
            return INT_MAX;
        }
        if(nums[i]+sum>limit){
            ans++;
            sum=nums[i];
        }else{
            sum+=nums[i];
        }
    }
    return ans;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    long long  a[n+1];
    long long r=0,l=0,mid;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        r+=a[i];
    }
    long long ans=r;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,a,n)<=k){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
