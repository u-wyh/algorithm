// https://www.luogu.com.cn/problem/P1324
// 题意：给 N×M 的木板和每条横竖切割线的单次切割费用。
// 每刀只能切一块当前存在的木板，沿格线切成两块。切开后不能拼回去。
// 求全部切成 1×1 时的最小总费用。
// 数据范围：1 ≤ N,M ≤ 2000，横切费用有 N-1 个，
// 竖切费用有 M-1 个，都是非负整数。
// 难度评分：1200（洛谷分级换算）
// 算法标签：贪心、排序

#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<n;i++){
        scanf("%d",&a[i]);
    }
    a[n]=0;
    for(int i=1;i<m;i++){
        scanf("%d",&b[i]);
    }
    b[m]=0;
    qsort(a+1,n-1,sizeof(int),cmp);
    qsort(b+1,m-1,sizeof(int),cmp);
    long long ans=0;
    int s1=1,s2=1;
    for(int i=2;i<n+m;i++){
        if(a[s1]>b[s2])
            ans+=s2*a[s1++];
		else
            ans+=s1*b[s2++];
    }
    printf("%lld\n",ans);
    return 0;
}
