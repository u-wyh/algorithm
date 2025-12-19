#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1005;

int n,m;

struct node{
    int p,s,ps;
};

node nums[MAXN];
node tmp[MAXN];

long long sum[MAXN];

bool cmp(node a,node b){
    return a.ps<b.ps;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i].p>>nums[i].s;
        nums[i].ps=nums[i].p+nums[i].s;
    }
    int res=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            tmp[j]=nums[j];
        }
        tmp[i].ps=tmp[i].ps-(tmp[i].p-tmp[i].p/2);
        sort(tmp+1,tmp+n+1,cmp);
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1]+tmp[i].ps;
        }
        int l=1,r=n,ans=0;
        while(l<=r){
            int mid=(l+r)/2;
            if(sum[mid]<=m){
                ans=mid;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        res=max(res,ans);
    }
    cout<<res<<endl;
    return 0;
}