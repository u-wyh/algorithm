// https://qoj.ac/problem/17412
// 题意：对长为 N 的整数序列 V，若末项非负，
// 且每项都不小于后续各项之和，V 就是超递减序列。
// 每组给 N、M，考虑长为 N 的整数序列 A、B，
// 两序列的元素都在 [1, M] 内。
// 要求对每个超递减 V，都有
// sum(A_i*V_i) >= sum(B_i*V_i)。
// 输出：每组输出合法序列对数对 998244353 取模。
// 数据范围：1 <= T <= 100，1 <= N, M <= 5000。
// 所有组的 N 之和、M 之和各不超过 5000。
// 算法标签：动态规划、二阶差分、前缀和
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