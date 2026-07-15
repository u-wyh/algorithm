#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MOD = 104857601;

int n;
int phi[MAXN];
int prime[MAXN];
int cnt=0;
bool vis[MAXN];

void euler(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=prime[j]*phi[i];
                break;
            }
            else{
                phi[i*prime[j]]=(prime[j]-1)*phi[i];
            }
        }
    }
    for(int i=1;i<=n;i++){
        phi[i]=(phi[i-1]+phi[i])%(MOD-1);
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
    cin>>n;
    euler(n);
    // for(int i=1;i<=n;i++){
    //     cout<<phi[i]<<' ';
    // }
    // cout<<endl<<endl;
    int P=1;
    for(int d=1;d<=n;d++){
        int k=n/d;
        int p=(2*phi[k]-1+MOD-1)%(MOD-1);
        P=(P*power(d,p))%MOD;
    }
    int N=1;
    for(int i=1;i<=n;i++){
        N=(N*i)%MOD;
    }
    N=power(N,2*n%(MOD-1));
    int ans=N*power(P,MOD-3)%MOD;
    cout<<ans<<endl;
    return 0;
}