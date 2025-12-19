#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;

int n,m,k,l;

bool a[MAXN],b[MAXN];
int cnta[MAXN],cntb[MAXN];

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

vector<pair<int,int>>ans;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++dfncnt;
    cnta[u]=a[u];
    cntb[u]=b[u];
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        if(!dfn[v]){
            tarjan(v,u);
            cnta[u]+=cnta[v];
            cntb[u]+=cntb[v];
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]){
                if(cnta[v]==0||cntb[v]==0||cnta[v]==k||cntb[v]==l){
                    ans.push_back({u,v});
                }
            }
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }
}

int main()
{
    n=read(),m=read(),k=read(),l=read();
    for(int i=1;i<=k;i++){
        int u=read();
        a[u]=true;
    }
    for(int i=1;i<=l;i++){
        int u=read();
        b[u]=true;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    tarjan(1,0);

    cout<<ans.size()<<endl;
    for(int i=0;i<(int)ans.size();i++){
        cout<<ans[i].first<<' '<<ans[i].second<<endl;
    }
    return 0;
}