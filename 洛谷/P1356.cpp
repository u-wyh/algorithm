#include<bits/stdc++.h>
using namespace std;

int dp[10005][105];
int n,k;
int arr[10005];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        dp[1][(arr[1]%k+k)%k]=dp[1][(-arr[1]%k+k)%k]=1;
        for(int i=2;i<=n;i++){
            for(int j=0;j<k;j++){
                dp[i][j]=dp[i-1][((j+arr[i])%k+k)%k]||dp[i-1][((j-arr[i])%k+k)%k];
            }
        }
        if(dp[n][0]){
            cout<<"Divisible"<<endl;
        }
        else{
            cout<<"Not divisible"<<endl;
        }
        for(int i=1;i<=n;i++){
            for(int j=0;j<k;j++){
                dp[i][j]=0;
            }
        }
    }
    return 0;
}
