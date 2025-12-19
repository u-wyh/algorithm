#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[355];
int a,b,c,d;
int dp[41][41][41][41];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=m;i++){
        int t;
        cin>>t;
        if(t==1){
            a++;
        }else if(t==2){
            b++;
        }else if(t==3){
            c++;
        }else if(t==4){
            d++;
        }
    }
    dp[0][0][0][0]=nums[1];
    for(int i=0;i<=a;i++){
        for(int j=0;j<=b;j++){
            for(int u=0;u<=c;u++){
                for(int v=0;v<=d;v++){
                    int now=1+i+j*2+u*3+v*4;
                    if(i)
                        dp[i][j][u][v]=max(dp[i][j][u][v],dp[i-1][j][u][v]+nums[now]);
                    if(j)
                        dp[i][j][u][v]=max(dp[i][j][u][v],dp[i][j-1][u][v]+nums[now]);
                    if(u)
                        dp[i][j][u][v]=max(dp[i][j][u][v],dp[i][j][u-1][v]+nums[now]);
                    if(v)
                        dp[i][j][u][v]=max(dp[i][j][u][v],dp[i][j][u][v-1]+nums[now]);

                }
            }
        }
    }
    cout<<dp[a][b][c][d]<<endl;
    return 0;
}
