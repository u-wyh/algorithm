// https://www.luogu.com.cn/problem/P4320
// 圆方树中方点是点双  圆点是每个单独的点   在树上，方点和圆点交互出现
// 每个点双和自己内部所有的点直接相连
// 从u到v必经过的点数就是最短路径上圆点出现的个数
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 1e6+5;
const int MAXH = 24;

int n,m,q,p;

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

int dep[MAXN<<1];
int sum[MAXN<<1];
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
    dep[u]=dep[fa]+1;
    st[u][0]=fa;

    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            // 这里的逻辑是 圆点点权为1 将点权赋给到父亲的那条边上
            sum[v]=sum[u]+(v<=n?1:0);
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
    tarjan(1,0);

    p=log2(cnt)+1;
    sum[1]=1;
    dfs(1,0);

    q=read();
    while(q--){
        int u,v;
        u=read(),v=read();
        int falca=lca(u,v);
        int ans=sum[u]+sum[v]-2*sum[falca]+(falca<=n?1:0);
        cout<<ans<<endl;
    }
    return 0;
}