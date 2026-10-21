#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 3e3+5;
const int INF = 1e16;

int n,m,x,y,z;
int cost[MAXN][MAXN];
int cost1[MAXN];
int a[MAXN];
int b[MAXN];
int dp[MAXN];
int pre[MAXN];
int ndp[MAXN];
int minval;

void solve(){
    cin>>n>>m>>x>>y>>z;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
    }

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cost[i][j]=j*z+abs(a[j]-b[i])*y;
        }
    }
    for(int i=1;i<=n;i++){
        cost1[i]=(i-1)*z;
    }

    for(int j=1;j<=n;j++){
        dp[j]=x+cost[1][j];
    }

    for(int i=2;i<=m;i++){

        // 预处理前缀最小值和换块最小值
        pre[0]=INF;
        minval=INF;

        for(int j=1;j<=n;j++){
            pre[j]=min(pre[j-1],dp[j]-j*z);
            minval=min(minval,dp[j]+(n-j)*z);
        }

        for(int j=1;j<=n;j++){
            // 重新粘贴一份 a
            int best=minval+x;

            // 继续使用当前这份 a
            if(j>1){
                best=min(best,pre[j-1]);
            }

            ndp[j]=best+cost[i][j];
        }

        for(int j=1;j<=n;j++){
            dp[j]=ndp[j];
        }
    }

    int ans=INF;
    for(int j=1;j<=n;j++){
        ans=min(ans,dp[j]+(n-j)*z);
    }

    cout<<ans<<"\n";
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}