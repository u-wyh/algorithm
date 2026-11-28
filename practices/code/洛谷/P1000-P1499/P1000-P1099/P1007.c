// https://www.luogu.com.cn/problem/P1007
// 题意：桥上的位置是 1 到 L，给出 n 名士兵的初始位置，
// 每人以速度 1 朝未知方向走。
// 相向的两人碰面时同时掉头。走到 0 或 L + 1 就算离开。
// 在所有可能的初始方向中，输出全员撤离所需时间的最小值和最大值。
// 数据范围：1 ≤ L ≤ 5000，0 ≤ n ≤ L，初始位置两两不同。
// 难度评分：1200（洛谷分级换算）
// 算法标签：贪心

#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}


int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int L,n;
    scanf("%d %d",&L,&n);
    if(n==0){
        printf("0 0\n");
        return 0;
    }
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    int  maxans,minans=0;
    maxans=max(L+1-nums[1],nums[n]);
    for(int i=1;i<=n;i++){
        if(nums[i]>=L/2){
            minans=max(minans,L+1-nums[i]);
        }else{
            minans=max(minans,nums[i]);
        }
    }
    printf("%d %d\n",minans,maxans);
    return 0;
}
