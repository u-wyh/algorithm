#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MOD = 1e9+7;
const int LIMIT = 31;

int n;
int a[MAXN];
int c[MAXN];
int b[MAXN];
int cnt0[LIMIT];
int cnt1[LIMIT];
int p[LIMIT];

int c0[LIMIT];
int c1[LIMIT];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        c[i]=(c[i-1]^a[i]);
    }

    // for(int i=1;i<=n;i++){
    //     cout<<c[i]<<' ';
    // }
    // cout<<endl;

    // for(int i=n;i>=1;i--){
    //     c[i]=(c[i+1]^a[i]);
    // }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    int ans=0;
    int val=0;
    p[0]=1;
    for(int i=1;i<LIMIT;i++){
        p[i]=(p[i-1]*2)%MOD;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<LIMIT;j++){
            if(c[i]&(1<<j)){
                cnt1[j]++;
            }
            else{
                cnt0[j]++;
            }
        }
    }
    for(int i=0;i<LIMIT;i++){
        val=(val+cnt1[i]*p[i]%MOD)%MOD;
    }
    // cout<<1<<": "<<val<<' '<<b[1]<<endl;
    // for(int i=0;i<=3;i++){
    //     cout<<i<<":    "<<cnt0[i]<<' '<<cnt1[i]<<endl;
    // }
    // cout<<endl;
    ans=val*b[1]%MOD;
    int all=val;
    int res=0;
    for(int i=2;i<=n;i++){
        int tmp=all;
        for(int j=0;j<LIMIT;j++){
            if(a[i-1]&(1<<j)){
                tmp=(tmp-p[j]*(cnt1[j]-cnt0[j]))%MOD;
                swap(cnt1[j],cnt0[j]);
            }
            cnt0[j]--;
        }
        res=0;
        for(int j=0;j<LIMIT;j++){
            c0[j]++;
            if(a[i-1]&(1<<j)){
                swap(c0[j],c1[j]);
            }
            res=(res+p[j]*c1[j]%MOD)%MOD;
        }
        val=(val-res+tmp)%MOD;
        all=tmp;
        ans=(ans+val*b[i]%MOD)%MOD;
        // cout<<i<<": "<<val<<' '<<b[i]<<endl;
    }
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}