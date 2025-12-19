#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,m,mod;
// f[i][j]表示前i个数字（1 2 3 、、、 i） 组成数字之和为j的方案数
// i最大不能超过根号n（也就是m）
int f[MAXN];
// g[i][j]表示大于根号n（也就是m）的数字选择i个  和是j的方案数
int g[MAXB][MAXN];

signed main()
{
    scanf("%lld %lld",&n,&mod);
    m=sqrt(n);

    f[0]=1;
    for(int i=1;i<=m;i++){
        for(int j=i;j<=n;j++){
            f[j]=(f[j]+f[j-i])%mod;
        }
    }

    g[0][0]=1;
    for(int i=1;i<=m;i++){
        for(int j=i;j<=n;j++){
            // 表示将已经选择的i个数字 每个数字都加上1
            g[i][j]=g[i][j-i];
            if(j>m){
                // 表示新加入一个数字 m+1  因为添加的数字至少要大于m  
                // 这个数字可以变得更大  不过需要后续操作中的加一实现
                g[i][j]=(g[i][j]+g[i-1][j-(m+1)])%mod;
            }
        }
    }

    int ans=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            ans=(ans+f[i]*g[j][n-i])%mod;
        }
    }
    cout<<ans<<endl;
    return 0;
}