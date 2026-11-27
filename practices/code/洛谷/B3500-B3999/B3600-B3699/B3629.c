// https://www.luogu.com.cn/problem/B3629
// 题意：每吃一根冰棍会得到一根木棒，三根木棒可以再换一根冰棍。
// 要吃到 n 根，求最开始至少买多少根。
// 数据范围：1 ≤ n ≤ 10^8。
// 算法标签：二分答案、模拟

#include<stdio.h>

int check(int n){
    int ans=n;
    while(n>=3){
        ans+=n/3;
        n=n%3+n/3;
    }
    return ans;
}

int main()
{
    int n;
    scanf("%d",&n);
    int l=1,r=n,ans=n,mid;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)>=n){
            ans=mid;
            r=mid-1;
        }else {
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}

