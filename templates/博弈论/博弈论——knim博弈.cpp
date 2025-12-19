// https://www.luogu.com.cn/problem/P2490
//knim博弈是指有多个堆   每次可以选择1~k个堆拿走一个   最终没有球可以拿的选手输
//这种问题的答案是将所有堆的元素个数写成二进制形式
//如果每一位上的1的个数都是(k+1)的整数倍  那么这种状态就是必败态
//因为每次拿1~k个堆中的一个  对于每个二进制位而言最多不过影响k个1的数量
//而对手一定可以修复成符合要求的必败态给你   就是循环 直到输
//这道题的逻辑是求出所有必败的法案总数   用所有方案数减去必败的方案  就是答案
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 2e4+5;
const int MAXM = 1e4+5;
const int LEN = 15;//表示最多的二进制位

int n,k,d,m,all;
int fac[MAXN];
int inv[MAXN];
int dp[LEN+1][MAXM];//表示来到第i位  总共用了j个位置  的方案数

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(a*ans)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

void prepare(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

int comb(int a,int b){
    return fac[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main()
{
    cin>>n>>k>>d;
    m=k/2;
    all=n-k;//表示最多有多少个位置可供消耗
    prepare(n+m);
    dp[0][0]=1;
    for(int i=0;i<LEN;i++){
        for(int j=0;j<=all;j++){
            if(dp[i][j]==0){
                continue;
            }
            for(int c=0;c<=m;c+=(d+1)){
                //枚举这一个二进制位上的1的个数有几个  必须是d+1的倍数
                int ways=(dp[i][j]*comb(m,c))%MOD;//原来的方案数  *   这一位上带来的贡献
                int val=c*(1<<i);//实际消耗的位置个数是  这一位上的权值*这一位上有1的个数
                if(val+j<=all){
                    dp[i+1][j+val]=(dp[i+1][j+val]+ways)%MOD;
                }
            }
        }
    }
    int ans=0;
    for(int j=0;j<=all;j++){
        //枚举一共用了多少个位置  统计不合法方案的数量
        int res=all-j;
        ans=(ans+dp[LEN][j]*comb(res+m,m)%MOD)%MOD;
    }
    ans=((comb(n,k)-ans)%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}