// https://www.luogu.com.cn/problem/P4071
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MOD = 1e9+7;

int n;
int fac[MAXN];
int inv[MAXN];
int sum[MAXN];

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
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=0;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }

    int op=-1;
    sum[0]=inv[0];
    for(int i=1;i<=n;i++){
        sum[i]=(sum[i-1]+op*inv[i])%MOD;
        op*=-1;
    }
}

signed main()
{
    prepare(1000000);

    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        int ans=inv[m];
        ans*=sum[n-m];
        ans%=MOD;
        ans*=fac[n];
        ans%=MOD;

        ans=(ans+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}