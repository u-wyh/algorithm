// https://www.luogu.com.cn/problem/P2350
// 题意：test 组数据，
// 每组以质因数分解形式给出正整数 N = prod(p_i^{q_i})。
// 求最小的 x 使得 phi^x(N) = 1（phi 为欧拉函数）。
// 每组输出一行整数 x。
// 数据范围：test <= 50，1 <= p_i <= 10^5，
// 1 <= q_i <= 10^9，m <= 2000。
// 算法标签：线性筛、数论
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2005;

int cnt;
bool vis[MAXN];
int prime[MAXN];

long long a[MAXM],b[MAXM];
long long ans;
long long f[MAXN];

void euler(int n){
    f[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            f[i]=f[i-1];
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            f[i*prime[j]]=f[i]+f[prime[j]];
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

int main()
{
    euler(100000);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        ans=1;
        for(int i=1;i<=n;i++){
            cin>>a[i]>>b[i];
            ans+=((a[i]==2)?-1:0)+f[a[i]]*b[i];
        }
        cout<<ans<<endl;
    }
    return 0;
}