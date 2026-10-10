// https://www.luogu.com.cn/problem/P3172
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MOD = 1e9+7;

int N,K,L,H;

int cnt;
int prime[MAXN];
bool vis[MAXN];
int mu[MAXN];

void prepare(int n){
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;;
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
}

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

signed main()
{
    prepare(100000);
    cin>>N>>K>>L>>H;

    int l=(L+K-1)/K;
    int r=H/K;

    if(l>r){
        cout<<0<<endl;
        return 0;
    }

    int ans=(l==1)?1:0;
    for(int d=1;d<=(r-l);d++){
        if(mu[d]==0){
            continue;
        }
        int c=(r/d)-(l-1)/d;
        ans+=mu[d]*(power(c,N)-c);
        ans%=MOD;
    }
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}