#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e7+5;

int l,r;
int cnt;
bool vis[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(a*ans)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

void prepare(){
    if(l<=r/2){
        for(int i=l;i<=r/2;i++){
            for(int j=2*i;j<=r;j+=i){
                vis[j]=true;
                // cout<<i<<' '<<j<<endl;
            }
        }
    }
    for(int i=l;i<=r;i++){
        if(!vis[i]){
            cnt++;
        }
    }
}

signed main()
{
    cin>>l>>r;
    prepare();
    // cout<<cnt<<endl;
    int ans=power(cnt+1,MOD-2);
    ans=(ans*cnt)%MOD;
    for(int i=1;i<=(r-l+2);i++){
        ans=(ans*i)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}