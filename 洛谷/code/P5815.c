// https://www.luogu.com.cn/problem/P5815
// 题意：有 n 种普通牌各 c_i 张和 m 张 joker；
// 一套牌可由每种普通牌各 1 张，或 1 张 joker 配 n-1 种普通牌各 1 张组成，求最多能凑出多少套牌。
// 输入 n, m 及各 c_i；输出最多套牌数。
// 数据范围：2 <= n <= 50，0 <= m, c_i <= 5*10^8。
// 算法标签：二分答案、贪心
#include<stdio.h>
#include<stdbool.h>

bool check(long long x,int *nums,int n,int m){
    for(int i=1;i<=n;i++){
        if(nums[i]<x){
            m-=(x-nums[i]);
        }
        if(m<0)
            return false;
    }
    return true;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    long long  l=0,r=1e10,mid,ans;
    while(l<=r){
        mid=((r-l)>>1)+l;
        if(check(mid,nums,n,m)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
