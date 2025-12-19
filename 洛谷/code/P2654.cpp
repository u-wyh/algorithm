#include<bits/stdc++.h>
using namespace std;
#define int long long 

int n,m,k;
int dp[21][21];
int nums[21];
int sum[21];
int ord[11];
priority_queue<int,vector<int>,greater<int>>heap;

int compute(){
    sum[0]=0;
    for(int i=1;i<=2*m;i++){
        sum[i]=sum[i-1]+nums[i];
        // cout<<nums[i]<<' ';
    }
    // cout<<endl;
    for(int i=1;i<=2*m;i++){
        for(int j=1;j<=2*m;j++){
            dp[i][j]=INT_MAX;
        }
    }
    for(int i=1;i<=2*m;i++){
        dp[i][i]=0;
    }
    for(int len=2;len<=m;len++){
        for(int i=1;i<=2*m-len+1;i++){
            int j=i+len-1;
            for(int k=i;k<j;k++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]);
            }
        }
    }
    int ans=LLONG_MAX;
    for(int i=1;i<=m+1;i++){
        ans=min(ans,dp[i][i+m-1]);
    }
    return ans;
}

signed main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        heap.push(v);
    }
    int ans=0;
    for(int i=1;i<=k;i++){
        for(int j=1;j<=m;j++){
            int u;
            cin>>u;
            ord[u]=j;
        }
        int all=0;
        for(int j=1;j<=m;j++){
            int u=heap.top();
            heap.pop();
            nums[ord[j]]=u;
            all+=u;
        }
        for(int j=m+1;j<=2*m;j++){
            nums[j]=nums[j-m];
        }
        ans+=compute();
        heap.push(all);
    }
    cout<<ans<<endl;
    return 0;
}