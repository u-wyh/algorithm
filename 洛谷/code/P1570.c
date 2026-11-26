// https://www.luogu.com.cn/problem/P1570
// 题意：给 n 种配料的美味度 v 和制作时间 c，恰好选择 m 种。求所选配料的总美味度除以总时间的最大值，保留三位小数。
// 数据范围：1 ≤ m ≤ n ≤ 200，1 ≤ c[i],v[i] ≤ 10000，答案不超过 1000。

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int v,c;
    double div;
}coffee;

int cmp(const void *a,const void *b){
    coffee *ca=(coffee *)a;
    coffee *cb=(coffee *)b;

    return cb->div - ca->div;
}

double max(double a,double b){
    return a>b?a:b;
}

double check(double x,coffee *nums,int n,int m){
    double ans=0;
    for(int i=1;i<=n;i++){
        nums[i].div=1.0*nums[i].v-x*nums[i].c;
    }
    qsort(nums+1,n,sizeof(coffee),cmp);
    for(int i=1;i<=m;i++){
        ans+=nums[i].div;
    }
    return ans;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    coffee nums[n+1];
    double l=0,r=0,ans,mid;
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i].v);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i].c);
        r=max(r,1.0*nums[i].v/nums[i].c);
    }
    while(r-l>1e-6){
        mid=(l+r)/2;
        if(check(mid,nums,n,m)>0){
            ans=mid;
            l=mid;
        }else{
            r=mid;
        }
    }
    printf("%.3lf\n",ans);
    return 0;
}
