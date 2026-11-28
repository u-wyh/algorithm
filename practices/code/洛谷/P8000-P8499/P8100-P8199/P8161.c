// https://www.luogu.com.cn/problem/P8161
// 题意：共 M 周、有 N 门课（1..N），每周有 N 个课时，
// 第 i 个课时上课程 i。
// 在总共 N * M 个课时中的每一节，可选择：1) 上课，
// 使课程 i 的理解度增加 A_i；
// 2) 不上该课而任选一门课程 j 自学，使课程 j 的理解度增加 B_j。
// 初始所有课程理解度均为 0，非上课时间不学习。
// 求期末时 N 门课理解度的最小值的最大可能值。
// 第一行输入 N, M，第二行 N 个整数 A_1..A_N，
// 第三行 N 个整数 B_1..B_N。
// 输出一行一个整数。
// 数据范围：1 <= N <= 3*10^5，1 <= M <= 10^9，
// 1 <= A_i, B_i <= 10^9。
// 难度评分：1300（洛谷分级换算）
// 算法标签：二分答案、贪心
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct
{
    long long  a,b;
}study;

bool check(long long x,study *nums,int n,int m){
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i].a>=nums[i].b){
            if(nums[i].a*n<x){
                ans+=n;
                ans+=(x-nums[i].a*n+nums[i].b-1)/nums[i].b;
            }else{
                ans+=(x+nums[i].a-1)/nums[i].a;
            }
        }else{
            ans+=(x+nums[i].b-1)/nums[i].b;
        }
        if(ans>n*m)
            return false;
    }
    return true;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    study nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%lld",&nums[i].a);
    }
    for(int i=1;i<=n;i++){
        scanf("%lld",&nums[i].b);
    }
    long long l=0,r=1e18,mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
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

