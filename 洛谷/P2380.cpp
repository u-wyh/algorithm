#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[505][505],b[505][505];
int sumr[505][505],sumc[505][505];
int dp[505][505];

int main()
{
    cin>>n>>m;
    while(n+m!=0){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
                sumr[i][j]=sumr[i][j-1]+a[i][j];
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>b[i][j];
                sumc[i][j]=sumc[i-1][j]+b[i][j];
            }
        }
//        for(int i=1;i<=n;i++){
//            for(int j=1;j<=m;j++){
//                //这种方法是不对的  没有考虑到上面的部分可以不是向上的
//                dp[i][j][0]=sumr[i][j]+sumc[i-1][j]+max(dp[i-1][j-1][0],dp[i-1][j-1][1]);
//                dp[i][j][1]=sumc[i][j]+sumr[i][j-1]+max(dp[i-1][j-1][0],dp[i-1][j-1][1]);
//            }
//        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                dp[i][j]=max(dp[i-1][j]+sumr[i][j],dp[i][j-1]+sumc[i][j]);
            }
        }
        cout<<dp[n][m]<<endl;
        cin>>n>>m;
    }
    return 0;
}
