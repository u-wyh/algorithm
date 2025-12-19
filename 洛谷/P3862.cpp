#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 1e5+5;

int a[MAXN];
int b[MAXN];

void prepare(int n){
    a[3]=1,b[3]=2;
    for(int i=4;i<=n;i++){
        b[i]=(b[i-1]*(i-2)+1)%MOD;
    }
    for(int i=4;i<=n;i++){
        a[i]=(a[i-1]+((i-2)*(i-1)/2)%MOD*b[i-1])%MOD;
    }
    // for(int i=1;i<=10;i++){
    //     cout<<i<<": "<<a[i]<<' '<<b[i]<<endl;
    // }
}

signed main()
{
    prepare(100000);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int ans=(a[n-1]+((n-2)*(n-3)/2)%MOD*b[n-1]%MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}