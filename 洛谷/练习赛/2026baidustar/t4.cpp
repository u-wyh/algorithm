#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1505;
const int INF = 1e12;

int n;
int val[MAXN][MAXN];
int sum[MAXN][MAXN];
int edge[MAXN][MAXN];
int dp[MAXN][MAXN];

// int matchlt[MAXN];
// int matchrt[MAXN];
// int dislt[MAXN];
// int disrt[MAXN];
// bool vis[MAXN];
// bool bfs(){
//     queue<int>q;
//     for(int i=1;i<=n;i++){
//         dislt[i]=INF;
//     }
// }

inline int func(int x1,int y1,int x2,int y2){
    return sum[x2][y2]+sum[x1-1][y1-1]-sum[x2][y1-1]-sum[x1-1][y2];
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            cin>>val[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+val[i][j];
        }
    }
    for(int l=1;l<=n;l++){
        for(int r=l+1;r<=n;r++){
            edge[l][r]=edge[r][l]=func(1,l,l,r-1)+func(l+1,r,r,n);
        }
    }

    for(int len=1;len<=n;len++){
        for(int l=1;l<=n;l++){
            dp[len][l]=INF;
        }
    }
    for(int l=1;l<=n;l++){
        int r=l+2-1;
        dp[2][l]=edge[l][r];
    }

    for(int len=4;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            dp[len][l]=min(dp[len-2][l+2]+edge[l][l+1],dp[len-2][l+1]+edge[l][r]);
            for(int k=l+3;k+1<=r;k+=2){
                int len1=k-l-1;
                int len2=len-len1-2;
                dp[len][l]=min(dp[len][l],dp[len1][l+1]+dp[len2][k+1]+edge[l][k]);
            }
        }
    }

    cout<<dp[n][1]<<endl;
    return 0;
}