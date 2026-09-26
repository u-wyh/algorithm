// https://www.luogu.com.cn/problem/P2158
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;

int n;
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
    cin>>n;
    if(n==1){
        cout<<0<<endl;
        return 0;
    }
    prepare(n);
    long long ans=1;
    for(int i=1;i<n;i++){
        ans+=phi[i];
    }
    ans*=2;
    ans--;
    cout<<ans<<endl;
    return 0;
}