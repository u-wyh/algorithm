// https://www.luogu.com.cn/problem/P3093
// 题意：输入奶牛数 N，以及每头牛的产奶量 g_i 和截止时间 d_i。
// 从时间 0 开始，每头牛挤奶耗时 1 单位时间，
// 必须在时刻 d_i 之前（含时刻 d_i-1 开始、d_i 结束）完成才能拿到
// g_i 加仑奶。
// 求合理安排挤奶顺序和取舍后能获得的最大总产奶量。
// 输出一个整数表示最大产奶量。
// 数据范围：1 <= N <= 10000，1 <= d_i <= 10000，
// 1 <= g_i <= 1000。
// 算法标签：贪心、排序
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int d,g;
}milk;

int max(int a,int b){
    return a>b?a:b;
}

int cmp(const void *a,const void *b){
    milk *ma=(milk *)a;
    milk *mb=(milk *)b;

    return mb->g-ma->g;
}

int main()
{
    int n,t=0;
    scanf("%d",&n);
    milk nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].g,&nums[i].d);
        t=max(t,nums[i].d);
    }
    qsort(nums+1,n,sizeof(milk),cmp);
    int used[t+1];
    for(int i=1;i<=t;i++){
        used[i]=0;
    }
    used[0]=1;
    int ans=0;
    for(int i=1;i<=n;i++){
        if(used[nums[i].d]==0){
            used[nums[i].d]=1;
            ans+=nums[i].g;
        }else{
            while(nums[i].d>=1){
                nums[i].d--;
                if(used[nums[i].d]==0){
                    used[nums[i].d]=1;
                    ans+=nums[i].g;
                    break;
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
