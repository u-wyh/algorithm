#include<bits/stdc++.h>
using namespace std;

int n;
struct node{
    int w,v;
}arr[1005];
int dp[20010],ans;

bool cmp(node a,node b){
    return a.w+a.v<b.w+b.v;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i].w>>arr[i].v;
    }
    sort(arr+1,arr+n+1,cmp);
    for(int i=1;i<=n;i++){
        for(int j=arr[i].w+arr[i].v;j>=arr[i].w;j--){
            dp[j]=max(dp[j],dp[j-arr[i].w]+arr[i].v);
        }
    }
    for(int i=0;i<20009;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}
