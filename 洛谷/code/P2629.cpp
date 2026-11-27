// https://www.luogu.com.cn/problem/P2629
// 题意：长度为 n 的序列 A_i，初始和为 0，任选起点 k in [1,n] 按 k..n, 1..k-1 循环累加。
// 求有多少个起点 k 使得累加过程中的前缀和始终 >= 0。
// 输出合法起点个数。
// 数据范围：1 <= n <= 10^6，-10^3 <= A_i <= 10^3。
#include<cstdio>
#include<iostream>
// 算法标签：单调队列、前缀和、破环成链
using namespace std;
int n,head=1,tail,ans;
long long a[2000001],s[2000001],q[2000001];
int main()
{
    scanf("%d",&n);
    for(register int i=1;i<=n;i+=1)
        scanf("%lld",&a[i]);
    for(register int i=1;i<=n-1;i+=1)
        a[i+n]=a[i];
    for(register int i=1;i<=2*n-1;i+=1)
        s[i]=s[i-1]+a[i];
    for(register int i=1;i<=2*n-1;i+=1)
    {
        while(head<=tail&&max(i-n+1,1)>q[head])head++;
        while(head<=tail&&s[i]<=s[q[tail]])tail--;
        q[++tail]=i;
        if(i-n+1>0&&s[q[head]]-s[i-n]>=0)ans++;
    }
    printf("%d\n",ans);
    return 0;
}
