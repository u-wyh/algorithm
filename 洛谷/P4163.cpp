#include<bits/stdc++.h>
using namespace std;

int dp[1024][1005];
int fac[10];
int cnt[10];

int main()
{
    int T;
    cin>>T;
    fac[0]=1;
    for(int i=1;i<=10;i++){
        fac[i]=i*fac[i-1];
    }
    while(T--){
        string str;
        cin>>str;
        int n,m;
        cin>>m;
        n=str.length();
        for(int i=0;i<(1<<n);i++){
            for(int j=0;j<m;j++){
                dp[i][j]=0;
            }
        }
        for(int i=0;i<=9;i++){
            cnt[i]=0;
        }
        dp[0][0]=1;
        for(int i=1;i<(1<<n);i++){
            for(int j=0;j<n;j++){
                if(i&(1<<j)){
                    for(int k=0;k<m;k++){
                        dp[i][(k*10+str[j]-'0')%m]+=dp[i-(1<<j)][k];
                    }
                }
            }
        }
        for(int i=0;i<n;i++){
            cnt[str[i]-'0']++;
        }
        int ans=dp[(1<<n)-1][0];
        for(int i=0;i<=9;i++){
            ans/=fac[cnt[i]];
        }
        cout<<ans<<endl;
    }
    return 0;
}