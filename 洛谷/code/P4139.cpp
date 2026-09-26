// https://www.luogu.com.cn/problem/P4139
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

int power(int a,int b,int p){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%p;
        }
        b>>=1;
        a=(a*a)%p;
    }
    return ans;
}

int solve(int p){
    if(p==1){
        return 0;
    }
    return power(2,solve(phi[p])+phi[p],p);
}

signed main()
{
    prepare(10000000);
    int T;
    cin>>T;
    while(T--){
        int p;
        cin>>p;
        cout<<solve(p)<<endl;
    }
    return 0;
}