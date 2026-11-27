// https://www.luogu.com.cn/problem/P3619
// 题意：输入测试点数 Z，每个测试点给出任务数 n、初始时间 T，以及 n 个任务的限制 t_i 与时间增量 b_i。
// 按任意顺序依次完成这 n 个任务，执行第 i 个任务要求当前 T > t_i，完成后 T 变为 T + b_i，且任何时刻必须保证 T > 0。
// 若能完成全部 n 个任务输出 +1s，否则输出 -1s。
// 数据范围：Z <= 10，n <= 10^5，t_i <= 10^5，T <= 10^5，-10^5 <= b_i <= 10^5。
#include<stdio.h>
#include<stdlib.h>
// 算法标签：贪心、排序

typedef struct
{
    int a,b;
}time;

int cmp1(const void *a,const void *b){
    time *ta=(time *)a;
    time *tb=(time *)b;

    return tb->b - ta->b;
}

int cmp2(const void *a,const void *b){
    time *ta=(time *)a;
    time *tb=(time *)b;

    return ta->a - tb->a;
}

int cmp3(const void *a,const void *b){
    time *ta=(time *)a;
    time *tb=(time *)b;

    return (ta->a+ta->b)-(tb->a+tb->b);
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        int n,T;
        scanf("%d %d",&n,&T);
        time nums[n+1];
        for(int i=1;i<=n;i++){
            scanf("%d %d",&nums[i].a,&nums[i].b);
        }
        qsort(nums+1,n,sizeof(time),cmp1);
        int i;
        for(i=1;i<=n;i++){
            if(nums[i].b<0)
                break;
        }
        qsort(nums+1,i-1,sizeof(time),cmp2);
        qsort(nums+i,n-i+1,sizeof(time),cmp3);
        for(i=1;i<=n;i++){
            if(T>=nums[i].a&&T>0){
                T+=nums[i].b;
            }else{
                printf("-1s\n");
                break;
            }
            if(i==n){
                if(T>0)
                    printf("+1s\n");
                else{
                    printf("-1s\n");
                }
            }
        }
    }
    return 0;
}
