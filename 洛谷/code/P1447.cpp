// https://www.luogu.com.cn/problem/P1447
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

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
                break;
            }
            else{
                phi[i*pri[j]]=phi[i]*(pri[j]-1);
            }
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    if(n<m){
        swap(n,m);
    }
    prepare(n);
    long long ans=-1ll*n*m;
    for(int d=1;d<=m;d++){
        ans+=2ll*phi[d]*(n/d)*(m/d);
    }
    cout<<ans<<endl;
    return 0;
}