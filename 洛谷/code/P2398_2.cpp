// https://www.luogu.com.cn/problem/P2398
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int phi[MAXN];
int pri[MAXN];
int len;
bool vis[MAXN];

void prepare(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            phi[i]=i-1;
            pri[++len]=i;
        }
        for(int j=1;j<=len&&(i*pri[j]<=n);j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0){
                phi[i*pri[j]]=phi[i]*pri[j];
            }
            else{
                phi[i*pri[j]]=phi[i]*(pri[j]-1);
            }
        }
    }
}

int main()
{
    int n;
    cin>>n;
    prepare(n);
    long long ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j*j<=i;j++){
            if(i%j==0){
                ans+=1ll*j*phi[i/j];
                if(j*j!=i){
                    ans+=1ll*i/j*phi[j];
                }
            }
        }
    }
    ans*=2;
    ans-=1ll*(1+n)*n/2;
    cout<<ans<<endl;
    return 0;
}