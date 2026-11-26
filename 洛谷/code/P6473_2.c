// https://www.luogu.com.cn/problem/P6473
// 题意：匀速以每年 v 的速度推石上长 L 的山坡，有 n 个位于 a_i 的魔法，若施展某魔法则首次到达 a_i 时立即滚回山底重新推起。
// q 次询问 t_i，求最少施展几个魔法才能使到达山顶用时严格大于 t_i（无法做到输出 -1）。
// 数据范围：1 <= n, q <= 2*10^5，1 <= v <= L <= 10^9，1 <= a_i < L（a_i 互不相同）
// 1 <= t_i <= 10^9。
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(long long  *)b-*(long long  *)a);
}

bool check(int x,long long *nums,int limit,int L,int v){
    L+=nums[x];
    if((1.0*L/v-limit)>0)
        return true;
    else
        return false;
}

int main()
{
    int n,L,v;
    scanf("%d %d %d",&n,&L,&v);
    long long a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    qsort(a+1,n,sizeof(long long),cmp);
    for(int i=2;i<=n;i++){
        a[i]+=a[i-1];
    }
    a[0]=0;
    int m;
    scanf("%d",&m);
    long long  t;
    for(int i=1;i<=m;i++){
        scanf("%lld",&t);
        int l=0,r=n,mid,ans=-1;
        if(L*1.0/v>t){
            printf("0\n");
            continue;
        }
        while(l<=r){
            mid=l+((r-l)>>1);
            if(check(mid,a,t,L,v)){
                ans=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
