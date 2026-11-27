// https://www.luogu.com.cn/problem/P2695
// 题意：有 n 个恶龙的头（大小 a_i）和 m 名骑士（能力与花费均为 z_i）。
// 题意：每名骑士最多砍掉 1 个大小不超过 z_i 的头，并收取 z_i 金币。
// 题意：求砍掉所有头的最小总花费；若无法全部砍掉，输出 you died!。
// 输入：第一行输入 n, m，随后 n 行输入 a_i，再 m 行输入 z_i。
// 输出：输出最小花费整数，无解则输出 you died!。
// 数据范围：1 <= n, m <= 2 * 10^4。
// 数据范围：1 <= a_i, z_i <= 10^5。
#include<stdio.h>
#include<stdlib.h>
// 算法标签：贪心、排序、双指针

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    qsort(b+1,m,sizeof(int),cmp);
    int k=1,ans=0;
    for(int i=1;i<=m;i++)
    {
        if(b[i]>=a[k])
        {
            ans+=b[i];
            k++;
        }
        if(k==n+1)
            break;
    }
    if(k<=n)
        printf("you died!\n");
    else
        printf("%d\n",ans);
    return 0;
}
