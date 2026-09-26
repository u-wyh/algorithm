// https://www.luogu.com.cn/problem/P1891
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int phi[MAXN];
int pri[MAXN];
int len;
bool vis[MAXN];
int f[MAXN];

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
                break;
            }
            else{
                phi[i*pri[j]]=phi[i]*(pri[j]-1);
            }
        }
    }

    for(int d=1;d<=n;d++){
        for(int v=d;v<=n;v+=d){
            f[v]+=d*phi[d];
        }
    }
}

signed main()
{
    prepare(1000000);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int ans=n*(f[n]+1)/2;
        cout<<ans<<endl;
    }
    return 0;
}