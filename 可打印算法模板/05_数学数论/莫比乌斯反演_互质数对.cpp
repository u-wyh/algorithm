// 用途：用莫比乌斯反演统计 gcd(x,y)=d 的数对。
// 时间：预处理 O(N)，单次查询 O(√N)。
// 空间：O(N)。
// 注意：d>0；a/d、b/d 不超过 50000。
// 例题：https://www.luogu.com.cn/problem/P3455
// 题意：多次统计两区间中 gcd 恰为 d 的数对。
// 思路：除以 d 转成互质计数，按莫比乌斯函数求和并整除分块。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;

int prime[MAXN];
bool vis[MAXN];
int cnt;
// mu 的前缀和用于整除分块计算互质数对。
int mu[MAXN];
int sum[MAXN];

void prepare(int n){
    mu[1]=sum[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=cnt&&(i*prime[j]<=n);j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            else{
                mu[i*prime[j]]=-mu[i];
            }
        }
        sum[i]=sum[i-1]+mu[i];
    }
}

int calc(int n,int m){
    long long ans=0;
    if(n>m){
        swap(n,m);
    }
    for(int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans+=(sum[r]-sum[l-1])*(m/l)*(n/l);
    }
    return ans;
}

signed main()
{
    prepare(50000);
    int T;
    cin>>T;
    while(T--){
        int a,b,d;
        cin>>a>>b>>d;
        cout<<calc(a/d,b/d)<<endl;
    }
    return 0;
}
