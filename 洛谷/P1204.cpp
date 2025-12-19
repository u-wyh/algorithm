#include<bits/stdc++.h>
using namespace std;

struct range{
    int L,R;
}nums[5005];
int n,ans1=0,ans2=0;

bool cmp(const range a,const range b){
    return a.L < b.L;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].L>>nums[i].R;
    }
    sort(nums+1,nums+n+1,cmp);
    int l=nums[1].L,r=nums[1].R,ans1=nums[1].R-nums[1].L;
    for(int i=2;i<=n;i++){
        if(nums[i].L<=r){
            r=max(r,nums[i].R);
        }else{
            ans1=max(ans1,r-l);
            ans2=max(ans2,nums[i].L-r);
            l=nums[i].L;
            r=nums[i].R;
        }
    }
    cout<<ans1<<' '<<ans2;
    return 0;
}
