#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 1e6+5;

int n,m;
bool hate[MAXN][MAXN];

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

int col[MAXN];
bool ok[MAXN];
bool vis[MAXN<<1];

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

}

void init(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            hate[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        headg[i]=0;
        ok[i]=false;
    }
    for(int i=1;i<=cnt;i++){
        head[i]=0;
        vis[i]=false;
    }
    for(int i=1;i<=cnt;i++){
        dfn[i]=low[i]=0;
    }
    cntg=0,cntt=0;
    cnt=n;
}

int main()
{
    while(true){
        n=read(),m=read();
        if(n==0&&m==0){
            break;
        }
        init();
        for(int i=1;i<=m;i++){
            int u,v;
            u=read(),v=read();
            hate[u][v]=hate[v][u]=true;
        }
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(!hate[i][j]){
                    addedgeg(i,j);
                    addedgeg(j,i);
                }
            }
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                tarjan(i,0);
            }
        }
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                dfs(i,0);
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            if(!ok[i]){
                ans++;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}