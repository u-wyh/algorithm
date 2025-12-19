#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 205;

int n;
int arr[MAXN];
int dp[MAXN][260];

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    int ans=0;
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        //枚举每一个第一个点
        //每次更换枚举点的时候  dp不用初始化  因为每次都是从上一层转移的
        //而0层就是0  不会变
        for(int j=1;j<=n;j++){
            for(int k=0;k<=255;k++){
                if(i==j){
                    dp[j][k]=dp[j-1][k^arr[j]];
                }
                else{
                    dp[j][k]=(dp[j-1][k]+dp[j-1][arr[j]^k])%MOD;
                }
            }
        }
        ans+=dp[n][0];
        ans%=MOD;
        for(int j=arr[i]+1;j<=255;j++){
            ans=(ans+dp[n][j])%MOD;
        }
    }
    cout<<ans<<endl;
    return 0;
}
