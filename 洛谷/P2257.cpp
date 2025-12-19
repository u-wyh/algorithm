#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int mu[MAXN];
int pre[MAXN];
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
    for(int i=1;i<=cnt;i++){
        for(int j=prime[i];j<=n;j+=prime[i]){
            pre[j]+=mu[j/prime[i]];
        }
    }
    for(int i=1;i<=n;i++){
        pre[i]+=pre[i-1];
    }
}

long long compute(int a,int b){
    long long ans=0;
    if(a>b){
        swap(a,b);
    }
    for(int l=1,r;l<=a;l=r+1){
        r=min(a/(a/l),b/(b/l));
        ans+=1ll*(pre[r]-pre[l-1])*(a/l)*(b/l);
    }
    return ans;
}

signed main()
{
    prepare(MAXN-1);
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        cout<<compute(n,m)<<endl;
    }
    return 0;
}