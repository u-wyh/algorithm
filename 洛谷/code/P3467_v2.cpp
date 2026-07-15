#include<bits/stdc++.h>
using namespace std;
int n,ans,y,r;
int st[250005],nums[250005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>y>>nums[i];
    }
    int ans=n;
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]>=nums[i]){
            if(nums[i]==nums[st[r-1]])
                ans--;
            r--;
        }
        st[r++]=i;
    }
    cout<<ans;
    return 0;
}

