#include<bits/stdc++.h>
using namespace std;

int n,m,ans=0;
int l[300005],r[300005],nums[300005],cnt[300005];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>l[i]>>r[i];
        nums[l[i]]+=1,nums[r[i]+1]+=-1;
    }
    for(int i=1;i<=n;i++){
        nums[i]+=nums[i-1];
        if(nums[i]==0)
            ans++;
        if(nums[i]==1)
            cnt[i]=cnt[i-1]+1;
        else
            cnt[i]=cnt[i-1];
        //printf("%3d",nums[i]);
    }
    //printf("\n");
    for(int i=1;i<=m;i++){
        cout<<ans+(cnt[r[i]]-cnt[l[i]-1])<<endl;
    }
    return 0;
}
