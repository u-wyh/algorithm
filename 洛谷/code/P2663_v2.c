#include <stdio.h>
#define MAX_N 107
#define MAX_SUM 10007

int n;
int a[MAX_N];
int dp[MAX_N][MAX_SUM];
int sum;

int main()
{
    scanf("%d", &n);

    sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    //printf("%d\n",sum);
    /*for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=sum;j++)
        {
            dp[i][j]=0;
        }
    }*/
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j>=1; j--) {
            for (int k = (sum-1) >> 1; k >= a[i]; k--) {
                dp[j][k] = dp[j][k] | dp[j - 1][k - a[i]];
            }
        }
    }

    for (int i = (sum-1) >> 1; i >= 0; i--) {
        if (dp[n >> 1][i]) {
            printf("%d\n", i);
            return 0;
        }
    }
    return 0;
}
