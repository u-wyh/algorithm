#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m;
int nums[MAXN];

int onecount(int val){
    int ans=0;
    while(val){
        if(val&1){
            ans++;
        }
        val>>=1;
    }
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>nums[i];
        }
        int all=(1ll<<m)-1;
        int ans=0;
        if(n==1){
            cout<<0<<endl;
            continue;
        }

        for(int i=1;i<=n;i++){
            int low,high;
            if(i==1){
                low=nums[1]|nums[2];
                high=nums[1]&(all^nums[2]);
            }
            else if(i==n){
                low=nums[n-1]|nums[n];
                high=nums[n]&(all^nums[n-1]);
            }
            else{
                low=(nums[i-1]|nums[i])&(nums[i]|nums[i+1]);
                high=(nums[i]&(all^nums[i-1]))|(nums[i]&(all^nums[i+1]));
            }

            int res=(1<<(onecount(low)-onecount(high)))-1;
            ans+=res;
        }
        cout<<ans<<endl;
    }
    return 0;
}