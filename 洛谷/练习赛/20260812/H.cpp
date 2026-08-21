#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef __int128 i128;
const int MAXN = 2e5+5;
const int MOD = 998244353;

int n,x;
int val[MAXN];
int b[MAXN];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>x;
        for(int i=1;i<=n;i++){
            cin>>val[i];
        }
        if(x==1){
            int ans=0;
            for(int i=1;i<=n;i++){
                ans+=(val[i]%MOD);
                ans%=MOD;
            }
            ans=(ans+MOD)%MOD;
            cout<<ans<<endl;
            continue;
        }

        i128 all=0;
        for(int i=1;i<=n;i++){
            all+=val[i]/x;
            b[i]=val[i]%x;
            if(b[i]==(x-1)){
                b[i]=0;
            }
        }
        sort(b+1,b+n+1);

        for(int i=n;i>=1;i--){
            if(b[i]==0){
                break;
            }
            if((x-1-b[i])>all){
                break;
            }
            all-=(x-1-b[i]);
            b[i]=0;
        }

        all%=(x-1);
        long long ans=0;
        for(int i=1;i<=n;i++){
            ans=(ans+b[i])%MOD;
        }
        ans=(ans+(all%MOD))%MOD;
        ans=(ans+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}