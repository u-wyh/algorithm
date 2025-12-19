#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int nums[MAXN];
int cnt[1<<20];

int main()
{
    cin>>n;
    long long ans=0;
    cnt[0]=1;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        nums[i]^=nums[i-1];
        //printf("%3d",nums[i]);
        ans+=cnt[nums[i]]++;
    }
    cout<<ans;
    return 0;
}

