// https://www.luogu.com.cn/problem/P1090
// 题意：有 n 堆果子，第 i 堆有 a[i] 个。每次挑两堆合并，代价是这两堆的果子总数。
// 一直合并到只剩一堆，输出所有合并代价之和的最小值。
// 数据范围：1 ≤ n ≤ 10^4，1 ≤ a[i] ≤ 2 × 10^4，最小总代价小于 2^31。
// 算法标签：贪心、哈夫曼合并

#include<stdio.h>
#include<stdlib.h>

#define MAX 10000+5

int n,a[MAX],stack[MAX];

int cmp(const void *a,const void *b){
    return (*(int *)b - *(int *)a);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    for(int i=1;i<=n;i++){
        stack[i]=a[i];
    }
    int ans=0,size=n;
    while(size>=2){
        ans+=stack[size]+stack[size-1];
        int k=stack[size]+stack[size-1];
        size--;
        int i=size-1;
        while(k>=stack[i]&&i>=1){
            stack[i+1]=stack[i];
            i--;
        }
        stack[i+1]=k;
    }
    printf("%d\n",ans);
    return 0;
}
