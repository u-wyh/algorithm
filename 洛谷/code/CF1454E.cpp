#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dfncnt;
int dfn[MAXN];

int sz[MAXN];
int from[MAXN];
bool cycle[MAXN];

void prepare(){
    for(int i=1;i<=n;i++){
        head[i]=0;
        dfn[i]=0;
        cycle[i]=false;
    }
    cntg=1;
    dfncnt=0;
}

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u){
    dfn[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(dfn[v]==0){
            from[v]=u;
            dfs(v);
        }
        else if(dfn[u]<dfn[v]){
            cycle[u]=true;
            for(int j=v;j!=u;j=from[j]){
                cycle[j]=true;
            }
        }
    }
}

void calc(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!cycle[v]){
            calc(v,u);
            sz[u]+=sz[v];
        }
    }
}

long long compute(){
    dfs(1);
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(cycle[i]){
            calc(i,0);
            ans+=1ll*sz[i]*(sz[i]-1)/2+1ll*sz[i]*(n-sz[i]);
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        prepare();
        for(int i=1;i<=n;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        cout<<compute()<<endl;
    }
    return 0;
}