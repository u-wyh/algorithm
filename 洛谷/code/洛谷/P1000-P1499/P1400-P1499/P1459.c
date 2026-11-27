// https://www.luogu.com.cn/problem/P1459
// 题意：给一个只由 1、2、3 组成的序列，一次可交换任意两个位置，
// 求排成非降序的最少交换次数。
// 数据范围：1 ≤ n ≤ 1000，每项在 [1,3]。
// 算法标签：排序、贪心

#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    qsort(b+1,n,sizeof(int),cmp);
    int cnt[5]={0,0,0,0,0};
    for(int i=1;i<=n;i++){
        cnt[a[i]-b[i]+2]++;
    }
    if(cnt[4]==cnt[0]){
        printf("%d\n",cnt[4]+cnt[3]);
    }else {
        if(cnt[4]>cnt[0]){
            printf("%d\n",cnt[0]+cnt[3]+(cnt[4]-cnt[0])*2);
        }else{
            printf("%d\n",cnt[4]+cnt[1]+(cnt[0]-cnt[4])*2);
        }
    }
    return 0;
}
