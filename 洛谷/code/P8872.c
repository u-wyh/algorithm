// https://www.luogu.com.cn/problem/P8872
// 题意：输入 n, m 和数组 a_1..a_n；
// 最多进行 m 次操作，每次可把一个当前最小值改为当前最大值，或把一个当前最大值改为当前最小值；
// 输出操作后能得到的最小极差（max - min）。
// 数据范围：1 <= n <= 10^5，0 <= m <= 10^9，|a_i| <= 10^9。
#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)a-*(int *)b);
}

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    if(m>=n-1){
        printf("0\n");
        return 0;
    }
    long long  ans=2e9;
    int j=1,i;
    for(i=1;i<=min(n,m+1);i++){
        j=j>i?j:i;
        while((i-1+n-j+min(i-1,n-j))>m)
            j++;
        ans=min(ans,a[j]-a[i]);
    }
    printf("%lld\n",ans);
    return 0;
}

