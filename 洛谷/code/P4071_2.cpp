// https://www.luogu.com.cn/problem/P4071
// 题意：多组询问，第一行输入测试数据组数 T，之后每行输入两个整数 n 和 m。
// 求有多少种 1 到 n 的排列 a，使得恰好有 m 个位置 i 满足 a_i = i。
// 每组输出一行整数，答案对 10^9 + 7 取模。
// 数据范围：1 <= T <= 5*10^5，1 <= n <= 10^6，0 <= m <= 10^6。
#include<bits/stdc++.h>
// 算法标签：组合数学、逆元、前缀和
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MOD = 1e9+7;

int n;
int fac[MAXN];
int inv[MAXN];
int sum[MAXN];

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

void prepare(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=0;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }

    int op=-1;
    sum[0]=inv[0];
    for(int i=1;i<=n;i++){
        sum[i]=(sum[i-1]+op*inv[i])%MOD;
        op*=-1;
    }
}

signed main()
{
    prepare(1000000);

    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        int ans=inv[m];
        ans*=sum[n-m];
        ans%=MOD;
        ans*=fac[n];
        ans%=MOD;

        ans=(ans+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}