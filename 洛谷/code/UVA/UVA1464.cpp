#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 1e5+5;
const int MAXH = 22;

int n,m,q,p;

int x[MAXM];
int y[MAXM];

int headg[MAXN];
int nxtg[MAXM<<1];
int tog[MAXM<<1];
int cntg=1;

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

bool vis[MAXN<<1];

int dep[MAXN<<1];
int st[MAXN<<1][MAXH];

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
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;

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
                while(sta[top]!=v){
                    int x=sta[top--];
                    addedge(cnt,x);
                    addedge(x,cnt);
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
    vis[u]=true;
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    // sum[u]=sum[fa]+(u<=n?1:0);

    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

inline int lca(int u,int v){
    if(dep[u]<dep[v]){
        swap(u,v);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[u][i]]>=dep[v]){
            u=st[u][i];
        }
    }
    if(u==v){
        return u;
    }

    for(int i=p;i>=0;i--){
        if(st[u][i]!=st[v][i]){
            u=st[u][i];
            v=st[v][i];
        }
    }
    return st[u][0];
}

void init(){
    for(int i=1;i<=cnt;i++){
        vis[i]=false;
        dfn[i]=0,low[i]=0;
    }
    top=0;
    dfncnt=0;
    for(int i=1;i<=n;i++){
        headg[i]=0;
    }
    for(int i=1;i<=cnt;i++){
        head[i]=0;
    }
    cntt=1,cntg=1;
    cnt=n;
}

int main()
{
    while(true){
        n=read(),m=read();
        if(n+m==0){
            break;
        }
        init();
        for(int i=1;i<=m;i++){
            int u,v;
            u=read(),v=read();
            addedgeg(u,v);
            addedgeg(v,u);
            x[i]=u,y[i]=v;
        }
        cnt=n;
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                tarjan(i,0);
            }
        }
        p=log2(cnt)+1;
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                dfs(i,0);
            }
        }

        q=read();
        while(q--){
            int s,t;
            s=read(),t=read();
            int ans=-1;
            int comb[4][2]={{x[s],x[t]},{x[s],y[t]},{y[s],x[t]},{y[s],y[t]}};
            for(int i=0;i<4;i++){
                int u=comb[i][0];
                int v=comb[i][1];
                int fa=lca(u,v);
                int len=(dep[u]+dep[v]-2*dep[fa])/2-1;
                ans=max(ans,len);
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}