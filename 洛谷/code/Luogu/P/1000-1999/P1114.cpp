#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int main()
{
    int n;
    cin>>n;
    int nums[n+1];
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        if(nums[i]==0){
            nums[i]=-1;
        }
    }
    map<int ,int >m;
    m[0]=0;
    int ans=0;
    for(int i=1;i<=n;i++){
        nums[i]+=nums[i-1];
        auto it=m.find(nums[i]);
        if(it!=m.end()){
            ans=max(ans,i- it->second );
        }
        else{
            m[nums[i]]=i;
        }
    }
    cout<<ans;
    return 0;
}
