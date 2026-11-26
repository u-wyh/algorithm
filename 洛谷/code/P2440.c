// https://www.luogu.com.cn/problem/P2440
// 题意：有 n 根长度分别为 L_i 的原木，需切割出至少 k 段等长正整数长度 l 的小段。
// 求 l 的最大值；若无法切出 1cm 的小段，输出 0。
// 数据范围：1 <= n <= 10^5，1 <= k <= 10^8，1 <= L_i <= 10^8。
#include<stdio.h>

int check(int x,int *nums,int n){
    int k=0;
    for(int i=1;i<=n;i++){
        k+=nums[i]/x;
    }
    return k;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    long long sum=0;
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        sum+=nums[i];
    }
    if(sum<=k){
        printf("0\n");
        return 0;
    }
    int l=1,r=1e8,mid,ans=0;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,n)>=k){
            l=mid+1;
            ans=mid;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
