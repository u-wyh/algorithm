// https://www.luogu.com.cn/problem/P4379
// 题意：N 头奶牛依次到达排队，第 i 头奶牛仅当到达时队伍人数不超过 w_i 才会入队，求所有可能到达顺序中最终排队奶牛数的最小值。
// 数据范围：1 <= N <= 10^5，0 <= w_i <= 10^9。
#include<stdio.h>
#include<stdlib.h>

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
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(cnt<=nums[i]){
            cnt++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
