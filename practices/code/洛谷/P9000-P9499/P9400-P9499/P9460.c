// https://www.luogu.com.cn/problem/P9460
// 题意：给定长度为 n 的序列 a。
// 可以进行 k 次修改操作，
// 每次把序列 b（初始为 a）的任意一个元素改为任意整数。
// 序列的众数定义为出现次数最大的所有整数（可多个并列）。
// 求有多少个不同的整数有可能成为修改后序列 b 的众数；
// 若无穷多输出 pigstd。
// 题意：第一行输入 n, k，第二行输入 a_1..a_n；
// 输出一个整数或 pigstd。
// 数据范围：1 <= n <= 10^6，0 <= k <= n，
// 1 <= a_i <= n。
// 难度评分：1300（洛谷分级换算）
// 算法标签：计数统计、排序
#include<stdio.h>
#include<stdlib.h>
#define Max 100000+5

int cnt[Max];

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    for(int i=0;i<=n;i++){
        cnt[i]=0;
    }
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        cnt[a[i]]++;
    }
    qsort(cnt,n+1,sizeof(int),cmp);
    if(k>=cnt[0]){
        printf("pigstd\n");
        return 0;
    }
    int ans=0;
    for(int i=0;i<=n;i++)
    {
        if(cnt[i]>=(cnt[0]-k))
            ans++;
        else
            break;
    }
    printf("%d\n",ans);
    return 0;
}
