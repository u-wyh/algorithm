#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

double dp[MAXN];
int n,k,c,w;
int op[MAXN],val[MAXN];

int main()
{
    cin>>n>>k>>c>>w;
    for(int i=1;i<=n;i++){
        cin>>op[i]>>val[i];
    }
    for(int i=n;i>=1;i--){
        if(op[i]==1){
            dp[i]=max(dp[i+1],val[i]+dp[i+1]*(1-0.01*k));
        }
        else{
            dp[i]=max(dp[i+1],dp[i+1]*(1+0.01*c)-val[i]);
        }
    }
    cout<<fixed<<setprecision(2)<<(dp[1]*w)<<endl;
    return 0;
}
