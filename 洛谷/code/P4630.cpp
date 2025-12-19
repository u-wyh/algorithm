#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

int n,m;

int headg[MAXN];
int nxtg[MAXM<<1];
int tog[MAXM<<1];
int cntg=1;

int val[MAXN<<1];
int sz[MAXN<<1];
int subsz;

int head[MAXN<<1];
int nxt[MAXN<<2];
int to[MAXN<<2];
int cntt=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int sta[MAXN],top;

// 方点编号  就是点双编号（类似于color）
int cnt;

long long ans;

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

inline void addedgeg(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

inline void addedge(int u,int v){
    nxt[cntt]=head[u];
    to[cntt]=v;
    head[u]=cntt++;
}

void tarjan(int u,int fa){
    subsz++;
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    val[u]=-1;

    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v==fa){
            continue;
        }

        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                cnt++;
                val[cnt]+=2;
                while(sta[top]!=v){
                    int x=sta[top--];
                    addedge(cnt,x);
                    addedge(x,cnt);
                    val[cnt]++;
                }
                top--;
                addedge(cnt,v);
                addedge(v,cnt);

                addedge(u,cnt);
                addedge(cnt,u);
            }
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }
}

void dfs(int u,int fa){
    sz[u]=(u<=n);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
            ans+=2ll*sz[u]*sz[v]*val[u];
            sz[u]+=sz[v];
        }
    }
    ans+=2ll*sz[u]*(subsz-sz[u])*val[u];
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedgeg(u,v);
        addedgeg(v,u);
    }
    cnt=n;
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            subsz=0;
            tarjan(i,0);
            dfs(i,0);
        }
    }
    cout<<ans<<endl;
    return 0;
}