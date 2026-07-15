#include<bits/stdc++.h>
using namespace std;

struct node{
    int a,b;
}nums[205];
int n,sum[205];
int f[205][205*205];

bool cmp(node a,node b){
    return a.b==b.b?a.a<b.a:a.b>b.b;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].a>>nums[i].b;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+nums[i].a;
    }
    //sum[0]=40000;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=sum[n];j++){
            f[i][j]=INT_MAX;
        }
    }
    f[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum[i];j++){
            if(j>=nums[i].a){
                f[i][j]=min(f[i][j],max(f[i-1][j-nums[i].a],j+nums[i].b));
            }
            f[i][j]=min(f[i][j],max(f[i-1][j],sum[i]-j+nums[i].b));
        }
    }
    int ans=INT_MAX;
    for(int i=0;i<=sum[n];i++){
        ans=min(ans,f[n][i]);
    }
    cout<<ans<<endl;
    return 0;
}
