#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;

set<int>node;

int headq[MAXN];
int nxtq[MAXN];
int ql[MAXN];
int qr[MAXN];
int cntq=1;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int dfn[MAXN];
int seg[MAXN];
int dfncnt;

int t[MAXN];

int pos[MAXN];
int tl[MAXN],tr[MAXN];

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

inline void add(int u,int l,int r){
    nxtq[cntq]=headq[u];
    ql[cntq]=l;
    qr[cntq]=r;
    headq[u]=cntq++;
}

void dfs(int u){
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=2;i<=n;i++){
        int u=read();
        addedge(u,i);
    }
    dfs(1);
    for(int i=1;i<=m;i++){
        pos[i]=read(),tl[i]=read(),tr[i]=read();
        add(pos[i],tl[i],tr[i]);
    }
    for(int i=1;i<=n;i++){
        t[i]=INT_MAX;
    }
    t[1]=0;
    for(int i=head[1];i;i=nxt[i]){
        int v=to[i];
        node.insert(dfn[v]);
        // cout<<1<<' '<<v<<endl;
    }
    for(int i=1;i<=m;i++){
        int u=pos[i];
        for(int j=tl[i];j<=tr[i];j++){
            if(t[u]!=INT_MAX){
                continue;
            }
            auto it=node.lower_bound(dfn[u]);
            if(*it!=dfn[u])
                it--;
            int v=seg[*it];
            // cout<<dfn[u]<<": "<<(*it)<<' '<<v<<' '<<dfn[v]<<endl;
            node.erase(dfn[v]);

            t[v]=j;
            for(int i=head[v];i;i=nxt[i]){
                int son=to[i];
                node.insert(dfn[son]);
                // cout<<v<<' '<<son<<endl;
            }
        }
    }
    int ans=INT_MAX;
    for(int u=1;u<=n;u++){
        for(int i=headq[u];i;i=nxtq[i]){
            int tl=ql[i],tr=qr[i];
            if(t[u]<=tl){
                ans=min(ans,tl);
            }
            else if(t[u]<=tr){
                ans=min(ans,t[u]);
            }
        }
    }
    if(ans==INT_MAX){
        ans=-1;
    }
    cout<<ans<<endl;
    return 0;
}