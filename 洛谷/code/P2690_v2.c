#include<stdio.h>

int max(int a,int b){
    return a>b?a:b;
}

int dp[1010][31],T,w,a[1010],ans;
int main()
{
    scanf("%d %d",&T,&w);
    for(int i=1;i<=T;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=T;i++){
        for(int j=0;j<=T&&j<=w;j++){
            if(j==0)
                dp[i][j]=dp[i-1][j];
            else
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]);
            if(a[i]==j%2+1)
                dp[i][j]++;
        }
    }
    for(int i=0;i<=w;i++)
        ans=max(ans,dp[T][i]);
    printf("%d\n",ans);
    return 0;
}
