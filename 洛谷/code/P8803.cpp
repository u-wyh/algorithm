#include<bits/stdc++.h>
using namespace std;

int month[13]={0,0,31,59,90,120,151,181,212,243,273,304,334};
int n,m,k;
struct node{
    int d,v;
}nums[1005];
bitset<5005>dp[1005];
int f[1005];

bool cmp(node a,node b){
    return a.d<b.d;
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        int m,d;
        cin>>m>>d>>nums[i].v;
        nums[i].d=month[m]+d;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        for(int j=i;j>=1;j--){
            if(nums[i].d-nums[j].d>=k){
                f[i]=j;
                break;
            }
        }
    }
    //dp[0][0]=1;
    dp[0].set(0,1);
    for(int i=1;i<=n;i++){
        dp[i]=(dp[i-1]|(dp[f[i]]<<nums[i].v));
//        for(int j=0;j<=m;j++){
//            dp[i][j]=dp[i-1][j];
//            if(j>=nums[i].v)
//                dp[i][j]|=dp[f[i]][j-nums[i].v];
//        }
    }
    for(int i=m;i>=0;i--){
        if(dp[n][i]){
            cout<<i<<endl;
            break;
        }
    }
    return 0;
}
