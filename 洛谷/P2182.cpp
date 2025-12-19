#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int MAXN = 105;

int n,k,m;
long long dp[MAXN][MAXN];
long long comb[MAXN][MAXN];
char a[MAXN],b[MAXN];

int main()
{
    scanf("%d %d %d",&n,&k,&m);
    scanf("%s %s",a+1,b+1);
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(a[i]!=b[i]){
            cnt++;
        }
    }
    comb[0][0]=1;
    for(int i=1;i<=n;i++){
        comb[i][0]=comb[i][i]=1;
        for(int j=1;j<i;j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }
    dp[0][cnt]=1;
    for(int i=1;i<=k;i++){
        for(int j=0;j<=n;j++){
            if(dp[i-1][j]==0){
                continue;
            }
            for(int p=0;p<=min(j,m);p++){
                if((m-p)>(n-j)){
                    continue;
                }
                int to=(j-p)+(m-p);
                if(to>=0&&to<=n){
                    dp[i][to]=(dp[i][to]+comb[j][p]*comb[n-j][m-p]%MOD*dp[i-1][j])%MOD;
                }
            }
        }
    }
    cout<<dp[k][0]<<endl;
    return 0;
}