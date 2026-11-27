// https://www.luogu.com.cn/problem/P9937
// 题意：有 N 篇论文，第 i 篇有 c_i 次引用。
// h 指数为满足“至少有 h 篇论文引用 >= h”的最大整数 h。
// 至多可选择 L 篇不同的论文使其引用数各增加 1，求之后能达到的最大 h 指数。
// 题意：第一行输入 N, L，第二行输入 c_1..c_N；输出一个整数。
// 数据范围：1 <= N <= 10^5，0 <= c_i <= 10^5，
// 0 <= L <= 10^5。
// 算法标签：二分答案、贪心
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

bool check(int x,int *nums,int n,int m){
    int k=0;
    for(int i=n;i>=n-x+1;i--){
        if(nums[i]>=x)
            k++;
        else if(nums[i]+1==x&&m>=1){
            m--;
            k++;
        }else{
            break;
        }
    }
    return k>=x;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    int l=nums[1],r=nums[n]+m,mid,ans;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,n,m)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
