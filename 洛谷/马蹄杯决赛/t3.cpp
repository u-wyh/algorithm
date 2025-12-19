#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n,m;
int nums[MAXN];

bool check(int x){
    int all=0;
    for(int i=1;i<=n;i++){
        all+=nums[i]/x;
    }
    return all<=m;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>nums[i];
        }
        int l=1,r=2e9,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)){
                ans=mid;
                r=mid-1;
            }
            else{
                l=mid+1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}