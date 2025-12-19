#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 11;

int n,k;
char s[MAXN];
int dp[MAXN][MAXN];

int getval(int l,int r){
    int res=0;
    for(int i=l;i<=r;i++){
        res=res*10+s[i]-'0';
    }
    return res;
}

signed main()
{
    scanf("%d %d %s",&n,&k,s+1);
    for(int i=1;i<=n;i++){
        dp[i][1]=getval(1,i);
    }
    for(int j=2;j<=k;j++){
        for(int i=j;i<=n;i++){
            for(int m=j-1;m<i;m++){
                dp[i][j]=max(dp[i][j],dp[m][j-1]*getval(m,i-1));
            }
        }
    }
    cout<<dp[n][k]<<endl;
    return 0;
}