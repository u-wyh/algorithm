// https://www.luogu.com.cn/problem/P225
// 实际对应：https://www.luogu.com.cn/problem/P2255
// 输入：第一行一个正整数 N，表示电视节目数量。
// 输入：接下来 N 行，每行两个整数 s_i, t_i，表示第 i 个节目的开始与结束时间。
// 题意：每个节目的播出时间为左闭右开区间 [s_i, t_i)。
// 题意：有一台双调谐器录音机，可同时录制最多两个节目（单个调谐器内所录节目时间不能重叠，端点相接可以）。
// 题意：求最多能完整录制的节目数量。
// 输出：输出一行一个整数，表示最大录制节目数。
// 数据范围：1 <= N <= 150
// 数据范围：0 <= s_i < t_i <= 10^9
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}cow;

int cmp(const void *a,const void *b){
    cow * ga=(cow *)a;
    cow * gb=(cow *)b;

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
    cow nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(cow),cmp);
    int ans=2;
    int t1=nums[1].b,t2=nums[2].b;
    for(int i=3;i<=n;i++){
        if(t1>t2){
            if(nums[i].a>=t1){
                ans++;
                t1=nums[i].b;
            }else if(nums[i].a>=t2){
                ans++;
                t2=nums[i].b;
            }
        }else{
            if(nums[i].a>=t2){
                ans++;
                t2=nums[i].b;
            }else if(nums[i].a>=t1){
                ans++;
                t1=nums[i].b;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
