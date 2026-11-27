#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;
int a[MAXN];
int b[MAXN];
int val[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=n;i++){
            cin>>b[i];
        }
        for(int i=1;i<=n;i++){
            val[i]=(a[i]-b[i])%m;
            if(val[i]<0){
                val[i]+=m;
            }
        }
        sort(val+1,val+n+1);
        int ans=min(val[n],m-val[1]);
        for(int i=1;i<n;i++){
            ans=min(ans,val[i]+m-val[i+1]);
        }
        cout<<ans<<endl;
    }
    return 0;
}