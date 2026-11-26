// https://www.luogu.com.cn/problem/B3637
// 题意：给一个长为 n 的序列，按原顺序挑出若干个数，使挑出的数严格递增。输出最多能挑多少个。
// 数据范围：1 ≤ n ≤ 5000，1 ≤ a[i] ≤ 10^6。

#include<stdio.h>

int main()
{
    long long n;
    scanf("%lld",&n);
    long long l=0,r=100000,mid,ans=0;
    while(l<=r){
        mid=(l+r)/2;
        if((mid*mid*mid)<=n){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
