#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 105;
const int INF = 1e15;

int n,k,d;
int nums[MAXN];
int dp[MAXN][MAXN][MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

signed main()
{
    n=read(),k=read(),d=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=k;j++){
            for(int p=0;p<=d;p++){
                dp[i][j][p]=-INF;
            }
        }
    }
    dp[0][0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=min(i,k);j++){
            for(int r=0;r<d;r++){
                dp[i][j][r]=dp[i-1][j][r];
                if(j>=1){
                    dp[i][j][r]=max(dp[i][j][r],dp[i-1][j-1][((r-nums[i])%d+d)%d]+nums[i]);
                }
            }
        }
    }
    if(dp[n][k][0]<0){
        cout<<-1<<endl;
    }
    else{
        cout<<dp[n][k][0]<<endl;
    }
    return 0;
}