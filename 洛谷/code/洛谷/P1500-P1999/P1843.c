// https://www.luogu.com.cn/problem/P1843
// 题意：给定 n 件衣服的湿度。
// 每秒所有衣服自然减少 a 点湿度，另可选至多一件额外减少 b 点。
// 求全部变干所需的最少秒数。
// 数据范围：1 ≤ n,a,b,w_i ≤ 5×10^5，湿度互不相同。
// 算法标签：二分答案、贪心、排序

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>

int cmp(const void *a,const void *b){
    return (*(int *)b-*(int *)a);
}

bool check(int x,int *nums,int n,int a,int b){
    int k=1;
    for(int i=1;i<=n;i++){
        if(nums[i]<=x*a)
            continue;
        else{
            k+=ceil(1.0*(nums[i]-x*a)/b);
        }
        if(k>n){
            return false;
        }
    }
    return true;
}

int main()
{
    int n,a,b;
    scanf("%d %d %d",&n,&a,&b);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    int l=1,r=nums[1],mid,ans=nums[1];
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,n,a,b)){
            r=mid-1;
            ans=mid;
        }else{
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
