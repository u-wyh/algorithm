// https://qoj.ac/contest/3516/problem/17412
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e3+5;
const int MOD = 998244353;

int T,n,m;
int dp[MAXN][MAXN];
int diff[MAXN];

int norm(int a){
    return (a%MOD+MOD)%MOD;
}

void add(int x,int v){
    diff[x]=norm(diff[x]+v);
}

void addrange(int l,int r,int a,int d){
    if(l>r){
        return ;
    }

    int len=r-l+1;
    add(l,a);
    add(l+1,d-a);
    add(r+1,-a-len*d);
    add(r+2,a+(len-1)*d);
}

int calc(int l,int r){
    int ans=0;

    // 第一部分：d<=0
    // 权重 m+d
    int L=l;
    int R=min(r,0LL);

    if(L<=R){
        int cnt=R-L+1;
        ans+=cnt*m+(L+R)*cnt/2;
    }

    // 第二部分：d>0
    // 权重 m-d
    L=max(l,1LL);
    R=r;

    if(L<=R){
        int cnt=R-L+1;
        ans+=cnt*m-(L+R)*cnt/2;
    }

    return norm(ans);
}

void solve(){
    cin>>n>>m;
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m+1;j++){
            dp[i][j]=0;
        }
    }

    dp[0][0]=1;

    for(int i=0;i<n;i++){
        for(int j=0;j<=m+1;j++){
            diff[j]=0;
        }
        for(int j=0;j<=m-1;j++){
            int v=dp[i][j];
            if(v==0){
                continue;
            }

            int l,r;
        
            l=-j,r=min(0ll,m-2-2*j);
            if(l<=r){
                int a=norm(v*(m+l));
                addrange(2*j+l,2*j+r,a,v);
            }

            l=1,r=m-2-2*j;
            if(l<=r){
                int a=norm(v*(m-l));
                addrange(2*j+l,2*j+r,a,-v);
            }

            l=max(-j,m-1-2*j),r=m-1;
            if(l<=r){
                int a=norm(calc(l,r)*v);
                addrange(m-1,m-1,a,0);
            }
        }

        for(int j=0;j<m;j++){
            diff[j]=(diff[j-1]+diff[j])%MOD;
        }
        for(int j=0;j<m;j++){
            diff[j]=(diff[j-1]+diff[j])%MOD;
            dp[i+1][j]=diff[j];
        }
    }

    int ans=0;
    for(int j=0;j<m;j++){
        ans=norm(ans+dp[n][j]);
    }
    cout<<ans<<endl;
}

signed main()
{
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}