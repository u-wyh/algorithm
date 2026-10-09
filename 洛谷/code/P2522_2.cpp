// https://www.luogu.com.cn/problem/P2522
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;

int prime[MAXN];
bool vis[MAXN];
int cnt;
// 莫比乌斯函数
int mu[MAXN];
int sum[MAXN];

void prepare(int n){
    mu[1]=sum[1]=1;
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
        sum[i]=sum[i-1]+mu[i];
    }
}

int calc(int n,int m,int d){
    n/=d;
    m/=d;
    long long ans=0;
    if(n>m){
        swap(n,m);
    }
    for(int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans+=(sum[r]-sum[l-1])*(m/l)*(n/l);
    }
    return ans;
}

signed main()
{
    prepare(50000);
    int T;
    cin>>T;
    while(T--){
        int a,b,c,d,k;
        cin>>a>>b>>c>>d>>k;
        int ans=calc(b,d,k);
        ans-=calc(a-1,d,k);
        ans-=calc(b,c-1,k);
        ans+=calc(a-1,c-1,k);
        cout<<ans<<endl;
    }
    return 0;
}