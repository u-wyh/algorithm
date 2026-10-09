// https://www.luogu.com.cn/problem/P2257
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int cnt;
int prime[MAXN];
bool vis[MAXN];
int mu[MAXN];
int g[MAXN];
int sum[MAXN];

void prepare(int n){
    mu[1]=1;
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
    }

    for(int i=1;i<=cnt;i++){
        int v=prime[i];
        for(int d=1;d*v<=n;d++){
            g[d*v]+=mu[d];
        }
    }

    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+g[i];
    }
}

int calc(int n,int m){
    if(n>m){
        swap(n,m);
    }
    int ans=0;
    for(int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans+=(sum[r]-sum[l-1])*(n/l)*(m/l);
    }
    return ans;
}

signed main()
{
    prepare(10000000);
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        cout<<calc(n,m)<<endl;
    }
    return 0;
}