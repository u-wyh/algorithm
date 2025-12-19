#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[500005];
int q[500005];
int h=0,t=0;
int ans=0;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        nums[i]+=nums[i-1];
        //printf("%3d",nums[i]);
    }
    //printf("\n");
    for(int i=0;i<=n;i++){
        while(h<t&&i-q[h]>m){
            h++;
        }
        //ans=max(ans,nums[i]-nums[q[h]]);
        while(h<t&&nums[i]<=nums[q[t-1]]){
            t--;
        }
        q[t++]=i;
        ans=max(ans,nums[i]-nums[q[h]]);
    }
    cout<<ans;
    return 0;
}
