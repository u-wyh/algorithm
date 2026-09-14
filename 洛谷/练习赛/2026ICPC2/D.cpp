#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = (1<<18)+5;
const int MAXM = (1<<19)+5;
const int MOD = 998244353;

int n,m,N;
int val[MAXM];
int limit[MAXM];
int pos[MAXN];
int cnt[MAXN];
int suf[MAXN];

int depth(int x){
    int dep=-1;
    while(x){
        dep++;
        x>>=1;
    }
    return dep;
}

bool isancestor(int x,int y){
    int dx=depth(x);
    int dy=depth(y);
    if(dx>dy){
        return false;
    }
    y>>=(dy-dx);
    return x==y;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    N=1<<n;
    bool flag=true;
    for(int i=1;i<=m;i++){
        int u,x;
        cin>>u>>x;

        if(val[u]&&val[u]!=x){
            flag=false;
            continue;
        }
        val[u]=x;

        if(pos[x]==0){
            pos[x]=u;
        }
        else{
            if(isancestor(pos[x],u)){
                pos[x]=u;
            }
            else if(isancestor(u,pos[x])){
                continue;
            }
            else{
                flag=false;
            }
        }
    }
    if(!flag){
        cout<<0<<endl;
        return 0;
    }

    limit[1]=N;
    if(val[1]){
        limit[1]=val[1];
    }

    for(int i=2;i<2*N;i++){
        limit[i]=limit[i>>1];
        if(val[i]){
            limit[i]=min(limit[i],val[i]);
        }
    }
    for(int i=N;i<2*N;i++){
        cnt[limit[i]]++;
    }

    for(int i=N;i>=1;i--){
        suf[i]=suf[i+1]+cnt[i];
    }
    int ans=1;
    for(int x=N;x>=1;x--){
        int ways=0;
        if(pos[x]==0){
            ways=suf[x]-(N-x);
        }
        else{
            int u=pos[x];
            int d=depth(u);
            int k=n-d;
            int lt=u<<k;
            int rt=((u+1)<<k)-1;

            for(int i=lt;i<=rt;i++){
                if(limit[i]==x){
                    ways++;
                }
            }
        }

        if(ways<=0){
            ans=0;
        }
        else{
            ans=(ans*ways)%MOD;
        }
    }
    cout<<ans<<endl;
    return 0;
}
/*
2 2
1 4
2 4
*/