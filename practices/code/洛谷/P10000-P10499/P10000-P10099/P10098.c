// https://www.luogu.com.cn/problem/P10098
// 题意：给 n 个共用电压 x 的发动机。
// 第 i 台在 x 不超过 z[i] 时功率为 a[i]×x，
// 超过后功率为 a[i]×z[i]+b[i]×(x-z[i])。
// 求总功率至少为 p 的最小整数电压。
// 数据范围：1 ≤ n ≤ 100，1 ≤ p ≤ 10^12，
// 1 ≤ z[i] ≤ 10^9，1 ≤ a[i],b[i] ≤ 10^4。
// 难度评分：1000（洛谷分级换算）
// 算法标签：二分答案

#include<stdio.h>

typedef struct
{
    long long  a,b,z;
}power;

long long check(long long mid,power *nums,int n){
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(mid>nums[i].z){
            ans+=(nums[i].b*(mid-nums[i].z)+nums[i].a*nums[i].z);
        }else{
            ans+=(nums[i].a*mid);
        }
    }
    return ans;
}

int main()
{
    int n;
    long long p;
    scanf("%d %lld",&n,&p);
    power nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%lld %lld %lld",&nums[i].z,&nums[i].a,&nums[i].b);
    }
    long long l=0,r=p,ans=p,mid;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,nums,n)>=p){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
