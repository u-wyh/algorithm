#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m;
struct node{
    int t,val;
}nums[MAXN];
int sum[MAXN];

bool cmp(node a,node b){
    return (a.t==b.t)?(a.val>b.val):(a.t<b.t);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    nums[0].t=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i].val>>nums[i].t;
    }
    sort(nums+1,nums+n+1,cmp);
    int t=n+1;
    for(int i=n;i>=1;i--){
        sum[i]=sum[i+1]+nums[i].val;
        if(sum[i]<m){
            t=i;
        }
    }
    int ans=0;
    if(t==1+n){
        ans=m*nums[n].t;
    }
    else{
        ans+=nums[t-1].t*m;
        for(int i=t;i<=n;i++){
            ans+=(nums[i].t-nums[t-1].t)*nums[i].val;
        }
    }
    cout<<ans<<endl;
    return 0;
}