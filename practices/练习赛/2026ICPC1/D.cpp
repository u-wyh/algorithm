#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MOD = 998244353;

int n;
int cnt[MAXN];
int p[MAXN];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        cnt[x]++;
    }

    int ans=1;
    for(int i=1;i<=n;i++){
        int x=p[i-1];
        int y=i-1-x;

        if(x>y){
            swap(x,y);
        }
        if(x==y){
            ans=(ans*2)%MOD;
        }

        if(cnt[x]){
            cnt[x]--;
            p[i]=x;
        }
        else{
            cnt[y]--;
            p[i]=y;
        }
    }
    cout<<ans<<endl;
    return 0;
}