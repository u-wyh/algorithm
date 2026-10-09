// https://www.luogu.com.cn/problem/P3455
// P3455 [POI2007] ZAP-Queries
// 题意：
// 给定 a,b,d，求有多少对 (x,y) 满足：
// 1 <= x <= a     1 <= y <= b    gcd(x,y) = d
// 先同时除以 d：
// gcd(x,y)=d  等价于  gcd(x/d,y/d)=1
// 所以问题转化为：
// 求 1<=x<=n，1<=y<=m 中 gcd(x,y)=1 的数对数量
// 利用莫比乌斯函数：
// [gcd(x,y)=1]  = sum_{k|x且k|y} mu(k)
//
// 交换枚举顺序：
// ans = sum_{k=1}^{min(n,m)}  mu(k) * floor(n/k) * floor(m/k)
// 由于 floor(n/k)、floor(m/k) 都具有整除分块性质
// 对于一段 [l,r]，它们的值保持不变
// 所以维护 mu 的前缀和：
// sumMu[i] = mu[1] + ... + mu[i]
// 每一段贡献：  (sumMu[r]-sumMu[l-1]) * (n/l) * (m/l)
// 时间复杂度： 预处理 O(N)
// 单次询问约 O(sqrt(N))
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;

int prime[MAXN];
bool vis[MAXN];
int cnt;
// 莫比乌斯函数
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