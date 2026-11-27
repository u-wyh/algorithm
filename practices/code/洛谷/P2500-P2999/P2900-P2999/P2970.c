// https://www.luogu.com.cn/problem/P2970
// 题意：输入奶牛数 N，以及每头牛喜欢吃草的直线区间 (S_i, E_i)。
// 任意两头奶牛 i, j 能同时吃草当且仅当两区间内部不重叠，
// 即 S_i >= E_j 或 E_i <= S_j。
// 求同一时刻最多可以有多少头奶牛同时吃草。
// 输出一行一个整数，表示最大同时吃草的奶牛数。
// 数据范围：对于 100% 的数据，1 <= N <= 50000，
// 1 <= S_i < E_i <= 10^8。
// 算法标签：贪心、排序
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}grass;

int cmp(const void *a,const void *b){
    grass * ga=(grass *)a;
    grass * gb=(grass *)b;

    if(ga->b > gb->b)
        return 1;
    if(ga->b < gb->b)
        return -1;
    return (gb->a-ga->a);
}

int main()
{
    int n;
    scanf("%d",&n);
    grass nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(grass),cmp);
    int ans=1;
    int t=nums[1].b;
    for(int i=2;i<=n;i++){
        if(nums[i].a>=t){
            ans++;
            t=nums[i].b;
        }
    }
    printf("%d\n",ans);
    return 0;
}
