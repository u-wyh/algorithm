// https://www.luogu.com.cn/problem/P4343
// 题意：有 l 条按时间顺序记录的代码行数变化日志 x_i（正数表示新写 x_i 行，负数表示删去 -x_i 行，删到 0 为止）；
// 一旦代码长度 >= n 就会立刻提交 AC 一题并清空重新开始写；
// 已知一共 AC 了 k 题，求阈值 n 可能的最小值和最大值（无解输出 -1）。
// 数据范围：1 <= l <= 1e5，-1e9 <= x_i <= 1e9，k > 0 且在 int 范围内。
#include<stdio.h>
#include<stdbool.h>

long long check(long long limit,long long *nums,int n){
    int ans=0;
    long long now=0;
    for(int i=1;i<=n;i++){
        if(now+nums[i]>=limit){
            ans++;
            now=0;
        }else if(now+nums[i]<=0){
            now=0;
        }else{
            now+=nums[i];
        }
    }
    return ans;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    long long nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%lld",&nums[i]);
    }
    long long l=1,r=1e15,mid,maxans=-1,minans=-1;
    while(l<=r){
        mid=((r-l)>>1)+l;
        if(check(mid,nums,n)>=k){
            if(check(mid,nums,n)==k) maxans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    l=1,r=1e15;
    while(l<=r){
        mid=((r-l)>>1)+l;
        if(check(mid,nums,n)<=k){
            if(check(mid,nums,n)==k) minans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    if(minans==-1)
        printf("-1\n");
    else
        printf("%lld %lld\n",minans,maxans);
    return 0;
}

