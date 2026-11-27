// https://www.luogu.com.cn/problem/P2240
// 题意：有 N 堆金币，第 i 堆重量 m_i、总价值 v_i，背包承重 T。
// 金币可任意分割且单位价值不变，求最多能装走多少价值的金币。
// 输出最大总价值，保留两位小数。
// 数据范围：N <= 100，T <= 1000，
// 1 <= m_i, v_i <= 100。
// 算法标签：贪心、排序
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int m,v;
    double div;
}gold;

int cmp(const void *a,const void *b){
    gold * ga=(gold *)a;
    gold * gb=(gold *)b;

    return gb->div - ga->div;
}

int main()
{
    int n,t;
    scanf("%d %d",&n,&t);
    gold nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].m,&nums[i].v);
        nums[i].div=1.0*nums[i].v/nums[i].m;
    }
    qsort(nums+1,n,sizeof(gold),cmp);
    double ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i].m<=t){
            t-=nums[i].m;
            ans+=nums[i].v*1.0;
        }else{
            ans+=nums[i].div*t;
            t=0;
        }
    }
    printf("%.2lf",ans);
    return 0;
}
