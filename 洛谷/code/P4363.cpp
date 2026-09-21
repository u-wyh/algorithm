// https://www.luogu.com.cn/problem/P4363
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;

int n,m;
int a[11][11];
int b[11][11];
int p[11];
unordered_map<int,int>dp;

int dfs(int state){
    auto it=dp.find(state);
    if(it!=dp.end()){
        return it->second;
    }

    int cur=state;
    int h[11];
    int cnt=0;
    for(int i=1;i<=n;i++){
        h[i]=cur%(m+1);
        cur/=(m+1);
        cnt+=h[i];
    }

    if(cnt==n*m){
        return 0;
    }

    int ans;
    if(cnt%2==0){
        ans=-INF;
        for(int i=1;i<=n;i++){
            if(h[i]==m){
                continue;
            }
            if(i>1&&h[i]==h[i-1]){
                continue;
            }
            int j=h[i]+1;
            int nxt=state+p[i];
            ans=max(ans,a[i][j]+dfs(nxt));
        }
    }
    else{
        ans=INF;
        for(int i=1;i<=n;i++){
            if(h[i]==m){
                continue;
            }
            if(i>1&&h[i]>=h[i-1]){
                continue;
            }
            int j=h[i]+1;
            int nxt=state+p[i];
            ans=min(ans,dfs(nxt)-b[i][j]);
        }
    }
    dp[state]=ans;
    return ans;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>b[i][j];
        }
    }
    p[1]=1;
    for(int i=2;i<=n;i++){
        p[i]=p[i-1]*(m+1);
    }

    cout<<dfs(0)<<endl;
    return 0;
}