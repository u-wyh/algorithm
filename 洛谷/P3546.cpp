#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int BASE = 499;
const int MOD = 1e9+7;

int n;
char s[MAXN];
int p[MAXN];
int h[MAXN];
int f[MAXN];

void build(){
    p[0]=1;
    for(int i=1;i<=n;i++){
        p[i]=p[i-1]*BASE;
        p[i]%=MOD;
    }
    for(int i=1;i<=n;i++){
        h[i]=h[i-1]*BASE+s[i]-'a'+1;
        h[i]%=MOD;
    }
}

int gethash(int l,int r){
    return ((h[r]-h[l-1]*p[r-l+1])%MOD+MOD)%MOD;
}

signed main()
{
    scanf("%lld %s",&n,s+1);
    if(n==1){
        cout<<0<<endl;
        return 0;
    }
    build();
    for(int i=n/2;i>=1;i--){
        f[i]=min(f[i+1]+2,(n-2*(i-1))/2);
        while(f[i]){
            if(gethash(i,i+f[i]-1)==gethash(n-f[i]-i+2,n-i+1)){
                break;
            }
            f[i]--;
        }
    }
    // for(int i=1;i<=n;i++){
    //     cout<<f[i]<<' ';
    // }
    // cout<<endl;
    int ans=f[1];
    for(int i=2;i<=n/2;i++){
        if(gethash(1,i-1)==gethash(n-i+2,n)){
            ans=max(ans,i-1+f[i]);
        }
    }
    if(gethash(1,n/2)==gethash(n-n/2+1,n)){
        ans=max(ans,n/2);
    }
    cout<<ans<<endl;
    return 0;
}