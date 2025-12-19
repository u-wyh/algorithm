#include<bits/stdc++.h>
using namespace std;

long long ans=0;
int n,m;
long long  nums[100005],a[100005],b[100005],c[100005],d[100005],cnt[100005];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i];
    }
    for(int i=1;i<n;i++){
        cin>>a[i]>>b[i]>>c[i];
        d[i]=(c[i]+(a[i]-b[i]-1))/(a[i]-b[i]);
    }
    for(int i=1;i<m;i++){
        long  L=min(nums[i],nums[i+1]);
        long  R=max(nums[i],nums[i+1]);
        cnt[L]+=1;
        cnt[R]-=1;
    }
    for(int i=1;i<n;i++){
        cnt[i]+=cnt[i-1];
        if(cnt[i]>=d[i]){
            ans+=c[i]+cnt[i]*b[i];
        }else{
            ans+=a[i]*cnt[i];
        }
        //printf("%3d",cnt[i]);
    }
    //printf("\n");
    cout<<ans;
    return 0;
}
