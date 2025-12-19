#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e16;

int n,k,s;
int fac[26];
int val[26];

int cnt;
int ans=0;
map<pair<int,int>,int>mp;

void dfs(int u,int limit,int sum,int d,int op){
    if(sum>s||d>k){
        return ;
    }
    if(u==limit+1){
        if(op==1){
            mp[{sum,d}]++;
        }
        else{
            for(int j=0;j<=k-d;j++){
                ans+=mp[{s-sum,j}];
            }
        }
    }
    else{
        dfs(u+1,limit,sum,d,op);
        dfs(u+1,limit,sum+val[u],d,op);
        if(val[u]<=18)
            dfs(u+1,limit,sum+fac[val[u]],d+1,op);
    }
}

signed main()
{
    cin>>n>>k>>s;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    fac[0]=1;
    for(int i=1;i<=18;i++){
        fac[i]=fac[i-1]*i;
    }
    dfs(1,(n+1)/2,0,0,1);
    dfs((n+1)/2+1,n,0,0,2);
    cout<<ans<<endl;
    return 0;
}