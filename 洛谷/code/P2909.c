// https://www.luogu.com.cn/problem/P2909
// 题意：输入奶牛数 N、高速车道数 M、减速值 D、最低限速 L，以及每头牛的初始最大速度 S_i。
// 每头牛选一条车道行驶，若同车道前面已有 K 头牛，则该牛实际速度为 max(S_i - D * K, 0)，且要求所有上路车辆速度均不低于 L。
// 选出尽可能多的奶牛并分配到 M 条车道中，使所有上路奶牛都符合最低限速。
// 输出一行一个整数，表示能够使用高速公路的最大奶牛数量。
// 数据范围：对于 100% 的数据，1 <= N <= 50000，1 <= M <= N，0 <= D <= 5000，1 <= L <= 1000000
// 1 <= S_i <= 1000000。
#include<stdio.h>
#include<stdlib.h>
// 算法标签：贪心、排序

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n,m,D,L,ans=0;
    scanf("%d %d %d %d",&n,&m,&D,&L);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    for(int i=1;i<=m;i++){
        int s=0;
        for(int j=1;j<=n;j++){
            if(!nums[j])
                continue;
            if(nums[j]-s*D>=L){
                s++;
                ans++;
                nums[j]=0;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
