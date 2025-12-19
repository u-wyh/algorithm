#include<bits/stdc++.h>
using namespace std;

int nums[1005][1005];
int n,k;
int ans=0;

int main()
{
    cin>>n>>k;
    for(int i=1,a,b,c,d;i<=n;i++){
        cin>>a>>b>>c>>d;
        nums[a+1][b+1]+=1;
        nums[c+1][d+1]+=1;
        nums[a+1][d+1]-=1;
        nums[c+1][b+1]-=1;
    }
    for(int i=1;i<=1000;i++){
        for(int j=1;j<=1000;j++){
            nums[i][j]+=nums[i-1][j]+nums[i][j-1]-nums[i-1][j-1];
        }
    }
    for(int i=1;i<=1000;i++){
        for(int j=1;j<=1000;j++){
            if(nums[i][j]==k){
                ans++;
            }
        }
    }
    cout<<ans;
    return 0;
}
