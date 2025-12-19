#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[5000005],d[5000005],minans=1e5;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        d[i]=nums[i]-nums[i-1];
    }
    while(m--){
        int l,r,z;
        cin>>l>>r>>z;
        d[l]+=z;
        d[r+1]-=z;
    }
    for(int i=1;i<=n;i++){
        d[i]+=d[i-1];
        minans=min(minans,d[i]);
    }
    cout<<minans;
    return 0;
}
