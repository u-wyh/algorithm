// https://www.luogu.com.cn/problem/P8647
// 题意：输入 N, K 和 N 块矩形大小 (H_i, W_i)，
// 从中切出至少 K 块边长相同的整数边长正方形（不能拼接），
// 保证至少能切出 K 块 1*1
// 输出最大可能的正方形边长。
// 数据范围：1 <= N, K <= 10^5，
// 1 <= H_i, W_i <= 10^5。
// 难度评分：1000（洛谷分级换算）
// 算法标签：二分答案
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct
{
    int l,w;
}choloate;

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

int check(int limit,choloate *nums,int n){
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=((nums[i].l/limit)*(nums[i].w/limit));
    }
    return ans;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    choloate nums[n+1];
    int l=1,r=0,mid,ans=1;
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].l,&nums[i].w);
        r=max(r,max(nums[i].l,nums[i].w));
    }
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,n)>=k){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
