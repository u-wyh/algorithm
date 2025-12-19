#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
struct node{
    int l,r;
}nums[MAXN];
int ans=0;

bool cmp(node a,node b){
    return a.l==b.l?(a.r<b.r):a.l<b.l;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].l>>nums[i].r;
    }
    sort(nums+1,nums+n+1,cmp);
    int st=nums[1].l,en=nums[1].r;
    for(int i=2;i<=n;i++){
        if(nums[i].l>en){
            ans+=en-st+1;
            st=nums[i].l;
            en=nums[i].r;
        }
        else{
            en=max(en,nums[i].r);
        }
    }
    ans+=(en-st+1);
    cout<<ans<<endl;
    return 0;
}