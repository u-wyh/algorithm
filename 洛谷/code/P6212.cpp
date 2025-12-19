#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;

int n,m,a,b;
char s[2025];
int nums[2025];
int inv;
int t;
int dp[2][2025][3][2];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

inline void addgb(int i){
    int p=i&1;
    for(int j=0;j<i;j++){
        for(int k=0;k<2;k++){
            dp[p][j][k][0]=(dp[p][j][k][0]+dp[p^1][j][k+1][1])%MOD;
        }
    }
}

inline void addbg(int i){
    int p=i&1;
    for(int j=1;j<i;j++){
        for(int k=1;k<3;k++){
            dp[p][j][k][1]=(dp[p][j][k][1]+dp[p^1][j-1][k-1][0])%MOD;
        }
    }
}

inline void addgg(int i){
    int p=i&1;
    for(int j=0;j<i;j++){
        for(int k=0;k<3;k++){
            dp[p][j][k][0]=(dp[p][j][k][0]+dp[p^1][j][k][0])%MOD;
        }
    }
}

inline void addbb(int i){
    int p=i&1;
    for(int j=0;j<i;j++){
        for(int k=0;k<3;k++){
            dp[p][j][k][1]=(dp[p][j][k][1]+dp[p^1][j][k][1])%MOD;
        }
    }
}

signed main()
{
    cin>>n>>m>>a>>b;
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        if(s[i]=='?'){
            t++;
        }
        if(s[i]=='?'){
            nums[i]=2;
        }
        else if(s[i]=='B'){
            nums[i]=1;
        }
        else{
            nums[i]=0;
        }
    }
    inv=power(2,t);
    inv=power(inv,MOD-2);

    if(nums[1]==2){
        dp[1][0][1][1]=dp[1][0][1][0]=1;
    }
    else{
        dp[1][0][1][nums[1]]=1;
    }

    for(int i=2;i<=n;i++){
        for(int j=0;j<i;j++){
            for(int k=0;k<3;k++){
                dp[i&1][j][k][0]=dp[i&1][j][k][1]=0;
            }
        }

        if(nums[i]==0){
            if(nums[i-1]==0){
                addgg(i);
            }
            else if(nums[i-1]==1){
                addgb(i);
            }
            else{
                addgb(i);
                addgg(i);
            }
        }
        else if(nums[i]==1){
            if(nums[i-1]==0){
                addbg(i);
            }
            else if(nums[i-1]==1){
                addbb(i);
            }
            else{
                addbb(i);
                addbg(i);
            }
        }
        else{
            if(nums[i-1]==0){
                addgg(i);
                addbg(i);
            }
            else if(nums[i-1]==1){
                addbb(i);
                addgb(i);
            }
            else{
                addgg(i);
                addbg(i);
                addbb(i);
                addgb(i);
            }
        }
    }

    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
            if (1ll * i * a - 1ll * (i - j + 1) * b >= m) {
                ans=(ans+dp[n&1][i][j][0]+dp[n&1][i][j][1])%MOD;
            }
        }
    }
    ans=(ans*inv%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}