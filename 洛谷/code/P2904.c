#include<stdio.h>
#include<limits.h>
#define N 2501

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    int sum[n+1];
    sum[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum[i]=sum[i-1]+nums[i];
    }
    for(int i=1;i<=n;i++)
        sum[i]+=2*m;
    int f[n+1];
    f[0]=0;
    for(int i=1;i<=n;i++)
        f[i]=INT_MAX;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (f[j - i] != INT_MAX) { // 确保f[j-i]不是无限大才进行更新
                f[j] = min(f[j] , f[j - i] + sum[i]); // 更新f[j]
            }
        }
    }
    printf("%d\n",f[n]-m);
    return 0;
}
