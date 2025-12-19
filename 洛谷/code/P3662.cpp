#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,k,m;
int nums[MAXN];
int sum[MAXN];

int main()
{
    cin>>n>>k>>m;
    for(int i=1;i<=m;i++){
        int a;
        cin>>a;
        nums[a]=1;
    }
    for(int i=1;i<k;i++){
        sum[i]+=sum[i-1]+nums[i];
    }
    int ans=INT_MAX;
    for(int i=k;i<=n;i++){
        sum[i]+=sum[i-1]+nums[i];
        sum[i]-=nums[i-k];
        ans=min(ans,sum[i]);
    }
    cout<<ans;
    return 0;
}
