// https://www.luogu.com.cn/problem/P9587
// 题意：给定长度 n 的数组 a 和整数 k。
// 定义 f(i) = (a 中严格大于 a_i 的元素个数) + 1，
// g(i) = (a 中大于等于 a_i 的元素个数)。
// 每次操作可选任意 t ∈ [1, n] 使 a_t 加 1。
// 对每个 i ∈ [1, n] 分别独立求
// 使得 f(i) <= k <= g(i) 成立的最少操作次数。
// 题意：第一行输入测试点编号 c 及 n, k，第二行输入 a_1..a_n；
// 输出 n 行，第 i 行为第 i 个位置的答案。
// 数据范围：1 <= k <= n <= 5 * 10^5，
// 1 <= a_i <= 10^9。
// 算法标签：排序、前缀和
#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(long long *)b-*(long long  *)a);
}

int main()
{
    int c,n,k;
    scanf("%d %d %d",&c,&n,&k);
    long long a[n+1],sum[n+1],ans=0;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    qsort(a+1,n,sizeof(long long),cmp);
    sum[0]=0;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i];
    }
    for(int i=1;i<=n;i++){
        if(a[i]<=a[k]){
            ans=(a[k]-a[i]);
        }else{
            ans+=((k-i)*a[i]-sum[k]+sum[i]);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
