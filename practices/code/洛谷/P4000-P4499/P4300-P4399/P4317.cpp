// https://www.luogu.com.cn/problem/P4317
// 题意：设 sum(i) 为正整数 i 的二进制表示中 1 的个数，给定正整数 N
// 求 sum(1) * sum(2) * ... * sum(N) 对
// 10000007 取模的结果。
// 数据范围：1 <= N <= 1e15。
// 难度评分：1800（洛谷分级换算）
// 算法标签：深度优先搜索、快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 51;
const int MOD = 1e7+7;

int n;
int f[MAXN];
int dp[MAXN][MAXN][2][MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

int dfs(int x,int val,int now,int need,int free){
    int ans=0;
    if(now>need||now+x+1<need){
        return 0;
    }
    if(x<0){
        return now==need;
    }
    // if(dp[x][now][free][need]!=-1){
    //     return dp[x][now][free][need];
    // }
    if(free){
        ans+=dfs(x-1,val,now+1,need,1);
        ans+=dfs(x-1,val,now,need,1);
    }
    else{
        if((val>>x)&1){
            ans+=dfs(x-1,val,now+1,need,0);
            ans+=dfs(x-1,val,now,need,1);
        }
        else{
            ans+=dfs(x-1,val,now,need,0);
        }
    }
    // dp[x][now][free][need]=ans;
    return ans;
}

void prepare(){
    for(int i=1;i*i<=MOD;i++){
        if(MOD%i==0){
            cout<<i<<endl;
        }
    }
}

signed main()
{
    // prepare();
    cin>>n;
    for(int i=0;i<=50;i++){
        for(int j=0;j<=50;j++){
            for(int k=0;k<=50;k++){
                dp[i][j][0][k]=-1;
                dp[i][j][1][k]=-1;
            }
        }
    }
    for(int i=1;i<=50;i++){
        f[i]=dfs(49,n,0,i,0);
    }
    int ans=1;
    for(int i=1;i<=50;i++){
        ans=(ans*power(i,f[i]))%MOD;
    }
    cout<<ans<<endl;
    return 0;
}