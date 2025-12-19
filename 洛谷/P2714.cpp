#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

int cnt;
int prime[MAXN];
bool vis[MAXN];

int mu[MAXN];

int num[MAXN];
int val[MAXN];

void prepare(int n){
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            mu[i]=-1;
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
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

long long comb(int x){
    if(x<4){
        return 0;
    }
    return 1ll*x*(x-1)*(x-2)*(x-3)/24;
}

int main()
{
    prepare(MAXN-1);
    int n;
    while(cin>>n){
        int maxx=0;
        for(int i=1;i<=n;i++){
            int v;
            cin>>v;
            val[v]++;
            maxx=max(maxx,v);
        }
        for(int d=1;d<=maxx;d++){
            for(int k=d;k<=maxx;k+=d){
                num[d]+=val[k];
            }
        }
        long long ans=0;
        for(int d=1;d<=maxx;d++){
            ans+=mu[d]*comb(num[d]);
        }
        cout<<ans<<endl;
        for(int i=1;i<=maxx;i++){
            val[i]=0;
            num[i]=0;
        }
    }
    return 0;
}