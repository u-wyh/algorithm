#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MOD = 998244353;
const int INV = 499122177;

int n;
int nums[MAXN];
// int dp[MAXN][2];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

long long power(int a,int b){
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

signed main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        // int k=0;
        int all=1;
        for(int i=1;i<=n;i++){
            nums[i]=read();
            if(nums[i]==-1){
                all*=2;
                all%=MOD;
            }
        }
        int two=all*INV%MOD;
        int four=two*INV%MOD;
        int ans=0;
        if(nums[1]==1){
            ans=(ans+all)%MOD;
        }
        else if(nums[1]==-1){
            ans=(ans+two)%MOD;
        }
        for(int i=2;i<=n;i++){
            if(nums[i]==1){
                if(nums[i-1]==0){
                    ans+=all;
                }
                else if(nums[i-1]==-1){
                    ans+=two;
                }
            }
            else if(nums[i]==-1){
                if(nums[i-1]==0){
                    ans+=two;
                }
                else if(nums[i-1]==-1){
                    ans+=four;
                }
            }
            ans%=MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}