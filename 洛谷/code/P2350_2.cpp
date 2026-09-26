// https://www.luogu.com.cn/problem/P2350
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int f[MAXN];
int pri[MAXN];
int len;
bool vis[MAXN];

void prepare(int n){
    f[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            pri[++len]=i;
            f[i]=f[i-1];
        }
        for(int j=1;j<=len&&(i*pri[j]<=n);j++){
            vis[i*pri[j]]=true;
            f[i*pri[j]]=f[i]+f[pri[j]];
        }
    }
}

int main()
{
    prepare(100000);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int ok=0;
        long long ans=1;
        for(int i=1;i<=n;i++){
            int a,b;
            cin>>a>>b;
            ans+=1ll*f[a]*b;
            if(a==2){
                ok++;
            }
        }
        ans-=ok;
        cout<<ans<<endl;
    }
    return 0;
}