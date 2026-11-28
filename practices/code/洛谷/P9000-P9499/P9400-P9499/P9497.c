// https://www.luogu.com.cn/problem/P9497
// 题意：给定 n * n 的矩阵 a，q 次独立询问，每次给定整数 v。
// 每次询问可以将矩阵的每一行各自任意重排，最大化“该列最大值 >= v”的列数。
// 题意：第一行输入 n, q，后 n 行输入矩阵 a，再 q 行输入 v；
// 输出 q 行答案。
// 数据范围：1 <= n <= 10^3，1 <= q <= 5 * 10^5，
// 1 <= a_{i,j}, v <= 10^9。
// 难度评分：900（洛谷分级换算）
// 算法标签：排序、二分查找
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)b - *(int *)a);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        qsort(a[i],n,sizeof(int),cmp);
    }
    while(m--){
        int x;
        scanf("%d",&x);
        int k=0;
        for(int i=0;i<n;i++){
            int l=0,r=n-1,mid,ans=-1;
            while(l<=r){
                mid=l+((r-l)>>1);
                if(a[i][mid]>=x){
                    ans=mid;
                    l=mid+1;
                }else{
                    r=mid-1;
                }
            }
            k+=(ans+1);
        }
        if(k>n)
            printf("%d\n",n);
        else
            printf("%d\n",k);
    }
    return 0;
}
