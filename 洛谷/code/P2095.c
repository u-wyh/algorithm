// https://www.luogu.com.cn/problem/P2095
// 题意：有 n 种分为 k 类的食品，每种有脂肪指数 a_i 和所属类别 b_i。
// 每种食品最多选一份，每顿最多吃 m 份，第 1 到 k 类各自不超过给定份数上限。
// 求在满足所有限制的前提下，能吃到的最大脂肪指数和。
// 数据范围：1 <= n <= 200，1 <= m, k <= 100。
// 1 <= a_i <= 100，1 <= b_i <= k，每类最多吃不超过 10 份。
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}food;

int cmp(const void *a,const void *b){
    food * fa=(food *)a;
    food * fb=(food *)b;

    if(fa->a > fb->a)
        return -1;
    if(fa->a < fb->a)
        return 1;

    return fa->b - fb->a;
}

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    int limit[k+1];
    for(int i=1;i<=k;i++){
        scanf("%d",&limit[i]);
    }
    food nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(food),cmp);
    int ans=0,cnt=0;
    for(int i=1;i<=n;i++){
        if(limit[nums[i].b]>=1){
            ans+=nums[i].a;
            cnt++;
            limit[nums[i].b]--;
        }
        if(cnt==m)
            break;
    }
    printf("%d\n",ans);
    return 0;
}
