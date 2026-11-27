// https://www.luogu.com.cn/problem/P3362
// 题意：输入 n、指数 d 和询问数 Q，定义 f(i) 为 i 的所有正约数 k 的 k^d 之和。
// 接下来 Q 行每行输入区间 [L_i, R_i]。
// 对每个询问输出 sum_{i=L_i}^{R_i} f(i) 对 10^9+7 取模的结果。
// 数据范围：n <= 10^7，d <= 10^18，Q <= 5*10^4，1 <= L_i <= R_i <= n。
#include<bits/stdc++.h>
// 算法标签：线性筛、快速幂、前缀和
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e7+5;

int n,d,q;
int f[MAXN];
int g[MAXN];
bool vis[MAXN];
int prime[MAXN];
int cnt;

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

signed main()
{
    cin>>n>>d>>q;
    d%=(MOD-1);
    f[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            f[i]=power(i,d)+1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]!=0){
                f[i*prime[j]]=(f[i]*f[prime[j]])%MOD;
            }
            else{
                int a=prime[j],b=i;
                while(b%prime[j]==0){
                    b/=prime[j];
                    a*=prime[j];
                }
                if(b==1){
                    f[i*prime[j]]=(f[i]+power(a,d))%MOD;
                }
                else{
                    f[i*prime[j]]=(f[a]*f[b])%MOD;
                }
                break;
            }
        }
    }
    for(int i=1;i<=n;i++){
        g[i]=(g[i-1]+f[i])%MOD;
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        int ans=(g[r]-g[l-1]+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}