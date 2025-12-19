#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

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
}

int main()
{
    cin>>n;
    euler(n+1);
    long long ans=0;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            ans+=phi[i+1];
            if(n/i!=i){
                ans+=phi[n/i+1];
            }
        }
    }
    ans++;
    ans/=2;
    cout<<ans<<endl;
    return 0;
}