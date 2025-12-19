#include<bits/stdc++.h>
using namespace std;

int n;
int nums[100005];
long long ans=0;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        ans+=max(nums[i]-nums[i-1],0);
    }
    cout<<ans;
    return 0;
}
