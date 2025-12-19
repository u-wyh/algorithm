#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 1005;

int n;

int dp[MAXN];

bool vis[MAXN];
int prime[MAXN];
int cnt;

void euler(){
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
        }

        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

signed main()
{
    cin>>n;
    euler();
    dp[0]=1;
    for(int i=1;i<=cnt;i++){
        for(int j=n;j>=prime[i];j--){
            int tmp=prime[i];
            while(j>=tmp){
                dp[j]=(dp[j]+dp[j-tmp]);
                tmp*=prime[i];
            }
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++){
        ans=(ans+dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}