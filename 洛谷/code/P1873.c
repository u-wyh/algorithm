// https://www.luogu.com.cn/problem/P1873
// 题意：给定 N 棵树的高度，把锯片设在整数高度 H，每棵树只截下超过 H 的部分。求能取得至少 M 米木材的最大 H。
// 数据范围：1 ≤ N ≤ 10^6，1 ≤ M ≤ 2×10^9。树高为正整数，洛谷满分数据树高 ≤ 4×10^5，总树高 > M。
// 算法标签：二分答案

#include<stdio.h>
#include<stdlib.h>

int check(int x,int *nums,int n,int m){
    int sum=0;
    for(int i=1;i<=n;i++){
        if(sum>=m)
            return sum;
        sum+=(nums[i]>x)?(nums[i]-x):0;
    }
    return sum;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1],max=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        max=max>nums[i]?max:nums[i];
    }
    int l=0,r=max,mid,ans=0;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,n,m)>=m){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
