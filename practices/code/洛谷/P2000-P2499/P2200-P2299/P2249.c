// https://www.luogu.com.cn/problem/P2249
// 题意：给定长度为 n 的单调不减非负整数序列，共 m 次询问。
// 每次询问整数 q 在序列中第一次出现的下标（从 1 开始），未找到输出 -1。
// 一行输出 m 个整数，空格隔开。
// 数据范围：1 <= n <= 10^6，1 <= m <= 10^5，
// 0 <= a_i, q <= 10^9。
// 难度评分：900（洛谷分级换算）
// 算法标签：二分查找
#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    while(m--){
        int k;
        scanf("%d",&k);
        int l=1,r=n,mid,ans=-1;
        while(l<=r){
            mid=((r-l)>>1)+l;
            if(nums[mid]>=k){
                if(nums[mid]==k) ans=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        printf("%d ",ans);
    }
    return 0;
}
