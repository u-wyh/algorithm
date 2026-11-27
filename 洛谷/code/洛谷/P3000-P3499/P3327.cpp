// https://www.luogu.com.cn/problem/P3327
// 题意：多组询问，第一行输入组数 T，每组给出两个整数 n、m。
// 设 d(x) 为 x 的约数个数，
// 求 sum_{i=1..n} sum_{j=1..m} d(i*j)。
// 对每组输出一行答案。
// 数据范围：1 <= T, n, m <= 50000。
// 算法标签：莫比乌斯反演、数论分块、线性筛
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

long long mu[MAXN];
long long f[MAXN];
bool vis[MAXN];
int prime[MAXN];
int cnt;

void prepare(int n){
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            else{
                mu[i*prime[j]]=-mu[i];
            }
        }
    }
    for(int i=1;i<=n;i++){
        mu[i]+=mu[i-1];
    }
    for(int i=1;i<=n;i++){
        for(int l=1,r;l<=i;l=r+1){
            r=(i/(i/l));
            f[i]+=(r-l+1)*(i/l);
        }
    }
}

long long compute(int a,int b){
    long long ans=0;
    if(a>b){
        swap(a,b);
    }
    for(int l=1,r;l<=a;l=r+1){
        r=min(a/(a/l),b/(b/l));
        ans+=1ll*(mu[r]-mu[l-1])*(f[a/l])*(f[b/l]);
    }
    return ans;
}

int main()
{
    prepare(MAXN-1);
    int T;
    cin>>T;
    while(T--){
        int a,b;
        cin>>a>>b;
        cout<<compute(a,b)<<endl;
    }
    return 0;
}