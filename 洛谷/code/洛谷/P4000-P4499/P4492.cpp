// https://www.luogu.com.cn/problem/P4492
// 题意：二叉树初始有根结点，之后每天等概率随机选一个未长出子结点的分支长出新结点
// 求第 N 天共 N 个结点时所有点对距离之和的期望 E 乘以 N! 后对 P
// 取模的结果。
// 数据范围：N <= 2000，P <= 10^9 + 7。
// 算法标签：组合数学
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2005;

int n,mod;
int fac[MAXN];
int comb[MAXN][MAXN];

signed main()
{
    scanf("%lld %lld",&n,&mod);
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%mod;
    }
    for(int i=0;i<=n;i++){
        comb[i][0]=comb[i][i]=1;
        for(int j=1;j<i;j++){
            comb[i][j]=(comb[i-1][j]+comb[i-1][j-1])%mod;
        }
    }
    int ans=0;
    for(int i=2;i<=n;i++){
        for(int sz=1;sz<=n-i+1;sz++){
            ans=(ans+((((((comb[n-i][sz-1]*fac[sz])%mod*(i-1))%mod*i)%mod*fac[n-sz-1])%mod*sz)%mod*(n-sz))%mod)%mod;
        }
    }
    cout<<ans<<endl;
    return 0;
}