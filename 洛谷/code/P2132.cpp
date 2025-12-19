#include<bits/stdc++.h>
using namespace std;

long long dp[31][31][31][31][31];
int n,a[5];

//每次放的都是   第  (a[0]+a[1]+a[2]+a[3]+a[4])-(a+b+c+d+e)+1  小 的数字
//那么这个数字一定是在最外层   一定是一条斜线 类似于 /
//如果有|这种直的线段  那么上面的位置是不能放的  否则会出现\这中形状  那么必然使得下端会比上端大
long long dfs(int a,int b,int c,int d,int e){
    if(a+b+c+d+e==0){
        return 1;
    }
    if(dp[a][b][c][d][e]){
        return dp[a][b][c][d][e];
    }
    long long ans=0;
    if(a>b) ans+=dfs(a-1,b,c,d,e);
    if(b>c) ans+=dfs(a,b-1,c,d,e);
    if(c>d) ans+=dfs(a,b,c-1,d,e);
    if(d>e) ans+=dfs(a,b,c,d-1,e);
    if(e) ans+=dfs(a,b,c,d,e-1);
    dp[a][b][c][d][e]=ans;
    return ans;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    cout<<dfs(a[0],a[1],a[2],a[3],a[4]);
    return 0;
}
