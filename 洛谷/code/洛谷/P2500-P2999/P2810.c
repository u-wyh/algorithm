// https://www.luogu.com.cn/problem/P2810
// 题意：输入一个整数 n，表示 4 只奶牛合法偷吃方案的总数。
// 4 只奶牛依次吃 a, a*k, a*k^2, a*k^3 吨食物，
// 其中正整数 a >= 1，整数倍数 k > 1
// 且每只吃的量不超过上限 m（即 a*k^3 <= m）。
// 已知满足条件的 (a, k) 方案数恰好为 n，求上限 m 的最小可能值。
// 输出一个整数表示最小的 m；若无解则输出 -1。
// 数据范围：对于 100% 的数据，n <= 10^15。
// 算法标签：二分答案、枚举
#include<stdio.h>

long long check(long long x){
    long long ans=0;
    for(long long i=2;i*i*i<=x;i++)
        ans+=x/(i*i*i);
    return ans;
}

int main()
{
    long long n,l=0,r=5e15,ans,mid;
    scanf("%lld",&n);
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid)<n){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n",check(ans+1)==n?(ans+1):-1);
    return 0;
}
