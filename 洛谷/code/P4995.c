// https://www.luogu.com.cn/problem/P4995
// 题意：地面高度 0，有 n 块高度互不相同的石头 h_i，小跳蛙从地面出发跳到每块石头上各一次并停在最后一块石头上
// 每次从 x 跳到 y 耗费 (x - y)^2 体力，求能耗费的最大体力值。
// 数据范围：1 <= n <= 300，0 < h_i <= 10^4 且 h_i 互不相同。
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
// 算法标签：贪心、排序、双指针

int cmp(const void *a,const void *b){
    return (*(int *)b-*(int *)a);
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    long long ans=nums[1]*nums[1];
    int l=1,r=n;
    while(l<r){
        ans+=pow(nums[l]-nums[r],2);
        l++;
        ans+=pow(nums[l]-nums[r],2);
        r--;
    }
    printf("%lld\n",ans);
    return 0;
}
