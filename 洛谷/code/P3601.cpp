#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 666623333;
const int MAXN = 1e6+5;

int l,r;

int cnt;
int prime[MAXN];
bool vis[MAXN];

int phi[MAXN];
int val[MAXN];

void prepare(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&prime[j]*i<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

signed main()
{
    cin>>l>>r;
    int n=ceil(sqrt(r));
    int len=r-l+1;
    prepare(n);
    for(int i=1;i<=len;i++){
        val[i]=i+l-1;
        phi[i]=i+l-1;
    }

    for(int i=1;i<=cnt;i++){
        int p=prime[i];
        int st=(l+p-1)/p*p;
        for(int j=st;j<=r;j+=p){
            int pos=j-l+1;
            val[pos]/=p;
            while(val[pos]%p==0){
                val[pos]/=p;
            }
            phi[pos]=phi[pos]/p*(p-1);
        }
    }
    for(int i=1;i<=len;i++){
        if(val[i]>1){
            phi[i]=phi[i]/val[i]*(val[i]-1);
        }
        phi[i]%=MOD;
    }
    int ans=0;
    for(int i=1;i<=len;i++){
        ans=(ans+i+l-1-phi[i])%MOD;
    }
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}