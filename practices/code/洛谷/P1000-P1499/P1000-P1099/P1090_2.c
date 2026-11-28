// https://www.luogu.com.cn/problem/P1090
// 题意：有 n 堆果子，第 i 堆有 a[i] 个。
// 每次挑两堆合并，代价是这两堆的果子总数。
// 一直合并到只剩一堆，输出所有合并代价之和的最小值。
// 数据范围：1 ≤ n ≤ 10^4，1 ≤ a[i] ≤ 2 × 10^4，
// 最小总代价小于 2^31。
// 难度评分：1200（洛谷分级换算）
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
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    int ans=0,size=n;
    while(size>=2){
        ans+=a[size]+a[size-1];
        int k=a[size]+a[size-1];
        size--;
        int i=size-1;
        while(k>=a[i]&&i>=1){
            a[i+1]=a[i];
            i--;
        }
        a[i+1]=k;
    }
    printf("%d\n",ans);
    return 0;
}

