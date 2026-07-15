#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;

int n,a,b,c;
int nums[MAXN];

bool check(int limit){
    for(int i=limit;i<=n;i++){
        if(nums[i]-nums[i-limit]>a*(b*i-c*(i-limit+1))){
            return true;
        }
    }
    return false;
}

signed main()
{
    cin>>n>>a>>b>>c;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        nums[i]+=nums[i-1];
    }
    int l=0,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}