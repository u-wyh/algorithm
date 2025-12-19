#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXM = 2505;

int n,m,t;
char s[MAXN];
int f[MAXM];
int dp[MAXN][MAXM];
int sum0[MAXN],sum1[MAXN];

int main()
{
    scanf("%d %d %d",&n,&m,&t);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<=m;j++){
            sum0[j]=sum0[j-1]+(s[j]=='0');
            sum1[j]=sum1[j-1]+(s[j]=='1');
        }
        for(int i=0;i<=m;i++){
            for(int j=0;j<=t;j++){
                dp[i][j]=0;
            }
        }
        for(int j=1;j<=m;j++){
            for(int k=1;k<=min(j,t);k++){
                for(int p=0;p<j;p++){
                    int zero=sum0[j]-sum0[p];
                    int one=sum1[j]-sum1[p];

                    dp[j][k]=max(dp[j][k],dp[p][k-1]+max(zero,one));
                }
            }
        }

        for(int j=t;j>=0;j--){
            for(int k=1;k<=j;k++){
                f[j]=max(f[j-k]+dp[m][k],f[j]);
            }
        }
    }
    int ans=0;
    for(int j=1;j<=t;j++){
        ans=max(ans,f[j]);
    }
    cout<<ans<<endl;
    return 0;
}