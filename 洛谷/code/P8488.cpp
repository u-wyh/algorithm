#include<bits/stdc++.h>
using namespace std;

int d[6][6]={{0,0,5,6,4,3},{0,0,6,5,3,4},
                {0,0,6,5,1,2},{5,6,0,0,2,1},{3,4,2,1,0,0},{4,3,1,2,0,0}};
int arr[1005][1005];
int nums[6];
int n,m;
int dp[1005][1005][6][6];

signed main()
{
    memset(dp,0xc0,sizeof(dp));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
        }
    }
    for(int i=0;i<6;i++){
        cin>>nums[i];
    }
    dp[1][1][0][3]=nums[5]*arr[1][1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int u=0;u<6;u++){
                for(int v=0;v<6;v++){
                    if(v==u||(v^1)==u||(i==1&&j==1)){
                        continue;
                    }
                    dp[i][j][u][v]=max(dp[i-1][j][d[u][v]][v],dp[i][j-1][u][d[u][v]])+arr[i][j]*nums[d[u][v]];
                }
            }
        }
    }
    int ans=0xc0c0c0c0;
    for(int u=0;u<6;u++){
        for(int v=0;v<6;v++){
            //cout<<u<<' '<<v<<endl;
            ans=max(dp[n][m][u][v],ans);
        }
    }
    cout<<ans<<endl;
    return 0;
}
