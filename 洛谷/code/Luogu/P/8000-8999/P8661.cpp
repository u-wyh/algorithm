#include<bits/stdc++.h>
using namespace std;

int n,d,k;
struct tiezi{
    int ts,id;
}nums[100005];
int sz=0;
int ans[100005];
int q[100005],cnt[100005];

int cmp(tiezi a,tiezi b){
    return a.ts<b.ts;
}

int main()
{
    cin>>n>>d>>k;
    for(int i=0;i<n;i++)
        cin>>nums[i].ts>>nums[i].id;
    sort(nums,nums+n,cmp);
    int h=0,t=0;
    for(int i=0;i<n;i++){
        while(h<t&&nums[i].ts-nums[q[h]].ts>=d){
            cnt[nums[q[h]].id]--;
            h++;
        }
        q[t]=i;
        cnt[nums[i].id]++;
        if(cnt[nums[i].id]>=k)
            ans[sz++]=nums[i].id;
        t++;
    }
    sort(ans,ans+sz);
    cout<<ans[0]<<endl;
    for(int i=1;i<sz;i++){
        if(ans[i]!=ans[i-1])
            cout<<ans[i]<<endl;
    }
    return 0;
}
