// https://www.luogu.com.cn/problem/P2723
// 题意：给定 k 个互不相同的质数集合 S，
// 求质因数全属于 S 的正整数（不含 1）中第 n 小的数。
// 输出第 n 小的数（保证在 32 位有符号整数范围内）。
// 数据范围：1 <= k <= 100，1 <= n <= 10^5，
// 2 <= p_i < 2^31。
// 算法标签：递推、多路归并
#include<cstdio>
int n,m;
int a[101],b[101];
int s[100001];

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    s[0]=1;
    for(int i=1;i<=m;i++)
    {
        int min=2147483647;
        for(int j=1;j<=n;j++)
        {
            while(a[j]*s[b[j]]<=s[i-1]) b[j]++;
            if(a[j]*s[b[j]]<min) min=a[j]*s[b[j]];
        }
        s[i]=min;
    }
    printf("%d",s[m]);
}
