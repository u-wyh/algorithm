#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 55;

int n;
int nums[MAXN];

int f[MAXN];

int fac[MAXN];
int inv[MAXN];

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

void prepare(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

int comb(int a,int b){
    if(b<0){
        return 0;
    }
    return fac[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    prepare(n);
    for(int i=1;i<=n;i++){
        if(nums[i]==n){
            cout<<(n-1)<<' ';
            continue;
        }

        int l=-1,r=n+1;
        for(int j=i-1;j>=1;j--){
            if(nums[j]>nums[i]){
                l=j;
                break;
            }
        }
        for(int j=i+1;j<=n;j++){
            if(nums[j]>nums[i]){
                r=j;
                break;
            }
        }

        if(l==-1){
            for(int j=1;j<=n-1;j++){
                f[j]=(comb(n-1-r+i,j+i-r)*power(comb(n-1,j),MOD-2))%MOD;
            }
        }
        else if(r==n+1){
            for(int j=1;j<=n-1;j++){
                f[j]=(comb(n-1-i+l,j+l-i)*power(comb(n-1,j),MOD-2))%MOD;
            }
        }
        else{
            for(int j=1;j<=n;j++){
                f[j]=((comb(n-1-r+i,j+i-r)*power(comb(n-1,j),MOD-2))%MOD+(comb(n-1-i+l,j+l-i)*power(comb(n-1,j),MOD-2))%MOD-(comb(n-1-r+l,j-r+l)*power(comb(n-1,j),MOD-2))%MOD+MOD)%MOD;
            }
        }

        int ans=0;
        for(int j=1;j<n;j++){
            ans=(ans+(j-1)*(f[j]-f[j-1])%MOD)%MOD;
        }
        ans=(ans+MOD)%MOD;
        cout<<ans<<' ';
    }
    return 0;
}