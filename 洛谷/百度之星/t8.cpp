#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e16;
const int MAXN = 2e5+5;

int n,x,y;
int nums[MAXN];

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>x>>y;
        for(int i=1;i<=n;i++){
            cin>>nums[i];
        }
        sort(nums+1,nums+n+1);
        int kind=1;
        for(int i=2;i<=n;i++){
            if(nums[i]!=nums[i-1]){
                kind++;
            }
        }
        int l=1,r=1;
        int ans=n*y;
        int op=0;
        while(l<=n){
            if(nums[l]>n){
                break;
            }
            op++;
            r=l;
            while(r+1<=n&&nums[r+1]==nums[l]){
                r++;
            }
            ans=min(ans,(n-r)*y+nums[l]*x);
            l=r+1;
        }

        if(kind==1){
            ans=0;
            cout<<ans<<endl;
            continue;
        }
        
        if(nums[n]<=n){
            ans=min(ans,nums[n]*x);
        }
        // if(kind==2){
        //     int len=1;
        //     for(int i=2;i<=n;i++){
        //         if(nums[i]==nums[1]){
        //             len++;
        //         }
        //     }
        //     ans=min(ans,min(len,n-len)*y);
        //     cout<<ans<<endl;
        //     continue;
        // }
        
        int maxx=0;
        l=1,r=1;
        while(l<=n){
            r=l;
            while(r+1<=n&&nums[r+1]==nums[l]){
                r++;
            }
            ans=min(ans,(n-r)*y+nums[l]*x);
            maxx=max(maxx,r-l+1);
            l=r+1;
        }
        ans=min(ans,(n-maxx)*y);
        cout<<ans<<endl;
    }
    return 0;
}