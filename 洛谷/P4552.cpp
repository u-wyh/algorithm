#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int nums[100005];
int d[100005];

signed main()
{
    cin>>n;
    int ans1=0,ans2=0;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        d[i]=nums[i]-nums[i-1];
        if(d[i]>0&&i!=1){
            ans1+=d[i];
        }
        if(d[i]<0&&i!=1){
            ans2-=d[i];
        }
    }
    int ans=0;
    cout<<max(ans1,ans2)<<endl;
    ans=abs(ans1-ans2)+1;
    cout<<ans<<endl;
    return 0;
}
