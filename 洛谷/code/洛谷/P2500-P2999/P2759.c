// https://www.luogu.com.cn/problem/P2759
// 题意：给定正整数 n，
// 求使得 x^x 在十进制下达到或超过 n 位数字的最小正整数 x。
// 输出最小正整数 x。
// 数据范围：1 <= n <= 2*10^9。
// 算法标签：二分答案、数学
#include<stdio.h>
#include<math.h>

long long check(long long  x){
    return x*log10(x)+1;
}

int main()
{
    int n;
    scanf("%d",&n);
    long long  l=1,r=n,mid,ans=n;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid)>=n){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
