#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e4+5;

int n;
int val[MAXN];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>val[i];
        }
        sort(val+1,val+n+1);
        int now=0;
        for(int i=n;i>=1;i--){
            now=max(now+val[i],2ll*val[i]);
        }
        cout<<now<<endl;
    }
    return 0;
}