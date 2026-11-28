// https://www.luogu.com.cn/problem/P10709
// 题意：有 n 人排成一列，第 i 人被邀请能贡献 a[i]。
// 可以不邀请任何人，也可以选若干人，只要原序列中相邻两人不同时入选。
// 求最大快乐总和。
// 数据范围：1 ≤ n ≤ 2 × 10^5，
// -10^9 ≤ a[i] ≤ 10^9。
// 难度评分：900（洛谷分级换算）
// 算法标签：贪心、排序

#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)b - *(int *)a);
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
    long long ans=0;
    if(n%2==0){
        for(int i=1;i<=n/2;i++){
            if(nums[i]<=0)
                break;
            else{
                ans+=nums[i];
            }
        }
    }else{
        for(int i=1;i<=n/2+1;i++){
            if(nums[i]<=0)
                break;
            else{
                ans+=nums[i];
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
