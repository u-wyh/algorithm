// https://www.luogu.com.cn/problem/P2887
// 题意：输入奶牛数 C、防晒霜种类数 L，
// 每头牛可接受的阳光强度范围 [minSPF[i], maxSPF[i]]
// 以及每种防晒霜的固定强度 SPF[i] 和瓶数 cover[i]。
// 每头牛最多涂一瓶防晒霜，涂后接收到的阳光强度稳定为 SPF[i]，
// 须落在该牛的区间内才能满足该牛。
// 合理分配防晒霜，最大化能够满足的奶牛数量。
// 输出一个整数，表示最多能满足日光浴的奶牛数目。
// 数据范围：对于 100% 的数据，1 <= C, L <= 2500，
// 1 <= minSPF[i] <= maxSPF[i] <= 1000
// 1 <= SPF[i] <= 1000，
// 1 <= cover[i] <= 2500。
// 难度评分：1200（洛谷分级换算）
// 算法标签：贪心、排序
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int min,max;
}cow;

typedef struct
{
    int num,spf;
}lotion;

int cmp(const void *a,const void *b){
    cow *ca=(cow *)a;
    cow *cb=(cow *)b;

    if(ca->max > cb->max)
        return 1;
    if(ca->max < cb->max)
        return -1;
    return ca->min - cb->min;
}

int cmp2(const void *a,const void *b){
    lotion * la=(lotion *)a;
    lotion * lb=(lotion *)b;

    return (lb->spf - la->spf);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    cow nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].min,&nums[i].max);
    }
    qsort(nums+1,n,sizeof(cow),cmp);
    lotion a[m+1];
    for(int i=1;i<=m;i++){
        scanf("%d %d",&a[i].spf,&a[i].num);
    }
    qsort(a+1,m,sizeof(lotion),cmp2);
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[j].num>0&&(a[j].spf>=nums[i].min&&a[j].spf<=nums[i].max)){
                ans++;
                a[j].num--;
                break;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}

