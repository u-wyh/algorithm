// μ(n) 求解过程:  μ(1)=1  
// μ(n)如果n的质数分解定理后  存在一个质数出现偶数次  那么是0
// 否则是-1
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int cnt;
int prime[MAXN];
bool vis[MAXN];
int phi[MAXN];
int mu[MAXN];

void prepare(int n){
    mu[1]=1,phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            phi[i]=i-1;
            mu[i]=-1;
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=prime[j]*phi[i];
                mu[i*prime[j]]=0;
                break;
            }
            else{
                phi[i*prime[j]]=(prime[j]-1)*phi[i];
                mu[i*prime[j]]=-mu[i];
            }
        }
    }
    for(int i=1;i<=n;i++){
        mu[i]+=mu[i-1];
        phi[i]+=phi[i-1];
    }
}