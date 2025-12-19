#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n,b;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int cap[MAXN];
int bel[MAXN];
int cntb;

int sta[MAXN];
int sz;

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    int x=sz;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        if(sz-x>=b){
            cap[++cntb]=u;
            while(sz!=x){
                bel[sta[sz--]]=cntb;
            }
        }
    }
    sta[++sz]=u;
}

int main()
{
    cin>>n>>b;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    if(cntb==0){
        cap[++cntb]=1;
    }
    while(sz>0){
        bel[sta[sz--]]=cntb;
    }
    cout<<cntb<<endl;
    for(int i=1;i<=n;i++){
        cout<<bel[i]<<' ';
    }
    cout<<endl;
    for(int i=1;i<=cntb;i++){
        cout<<cap[i]<<' ';
    }
    return 0;
}