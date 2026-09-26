// https://www.luogu.com.cn/problem/P2568
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

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

signed main()
{
    int n;
    cin>>n;
    prepare(n);
    for(int i=1;i<=n;i++){
        phi[i]+=phi[i-1];
    }
    int ans=0;
    for(int i=1;i<=len;i++){
        ans+=(2*phi[n/pri[i]]-1);
    }
    cout<<ans<<endl;
    return 0;
}