#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int mu[MAXN];//莫比乌斯函数
int prime[MAXN];
int cnt;
bool vis[MAXN];

//预处理莫比乌斯函数
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
}

int main()
{
    int a,b,d;
    cin>>a>>b>>d;
    a/=d;
    b/=d;
    int n=min(a,b);
    prepare(n);
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=(1ll*mu[i]*(a/i)*(b/i));
    }
    cout<<ans<<endl;
    return 0;
}