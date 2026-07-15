#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MOD = 1e9+7;

int n;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dfncnt;
int dfn[MAXN];

int cntb;
int from[MAXN];
int all[MAXN];
int cycle[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=ans*a;
            ans%=MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

void dfs(int u){
    all[cntb]++;
    dfn[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(dfn[v]==0){
            from[v]=u;
            dfs(v);
        }
        else if(dfn[u]<dfn[v]){
            for(int j=v;j!=u;j=from[j]){
                cycle[cntb]++;
            }
            cycle[cntb]++;
        }
    }  
}

int compute(){
    int ans=1;
    for(int i=1;i<=n;i++){
        if(dfn[i]==0){
            cntb++;
            dfs(i);
            int a=power(2,all[cntb]);
            int b=power(2,all[cntb]-cycle[cntb]+1);
            ans=(ans*((a-b+MOD)%MOD))%MOD;
        }
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        int u;
        cin>>u;
        addedge(i,u);
        addedge(u,i);
    }
    cout<<compute()<<endl;
    return 0;
}