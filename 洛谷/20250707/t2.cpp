#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int pre[32];
int nums[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=n;i++){
        int val=nums[i];
        int len=1;
        for(int j=0;j<31;j++){
            if(((val>>j)&1)==1){
                len=max(len,pre[j]+1);
            }
        }
        for(int j=0;j<31;j++){
            if(((val>>j)&1)==1){
                pre[j]=max(pre[j],len);
            }
        }
    }
    int ans=0;;
    for(int j=0;j<31;j++){
        ans=max(ans,pre[j]);
    }
    cout<<ans<<endl;
    return 0;
}