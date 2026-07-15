#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int INF = 1e9;

int n,k;
int col[MAXN];

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int headc[MAXN];
int nxtc[MAXN];
int toc[MAXN];
int cntc=1;

bool vis[MAXN];
int sz[MAXN];

int fa[MAXN];
int rt[MAXN];

int que[MAXN];
bool nodevis[MAXN];
bool colvis[MAXN];

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

inline void addedgec(int u,int v){
    nxtc[cntc]=headc[u];
    toc[cntc]=v;
    headc[u]=cntc++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(!vis[v]&&v!=fa){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=headg[u];i;i=nxtg[i]){
            int v=tog[i];
            if(!vis[v]&&v!=fa&&sz[v]>half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int f,int root){
    fa[u]=f;
    rt[u]=root;
    nodevis[u]=false;
    colvis[col[u]]=false;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=f&&!vis[v]){
            dfs(v,u,root);
        }
    }
}

int calc(int u){
    dfs(u,0,u);
    int ans=0;
    int l=1,r=0;
    que[++r]=u;
    nodevis[u]=true;
    while(l<=r){
        int cur=que[l++];
        if(cur!=u&&!nodevis[fa[cur]]){
            que[++r]=fa[cur];
            nodevis[fa[cur]]=true;
        }
        if(!colvis[col[cur]]){
            colvis[col[cur]]=true;
            ans++;
            for(int i=headc[col[cur]];i;i=nxtc[i]){
                int v=toc[i];
                if(rt[v]!=u){
                    return INF;
                }
                if(!nodevis[v]){
                    nodevis[v]=true;
                    que[++r]=v;
                }
            }
        }
    }
    return ans;
}

int solve(int u){
    vis[u]=true;
    int ans=calc(u);
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(!vis[v]){
            ans=min(ans,solve(getcentroid(v,u)));
        }
    }
    return ans;
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedgeg(u,v);
        addedgeg(v,u);
    }
    for(int i=1;i<=n;i++){
        col[i]=read();
        addedgec(col[i],i);
    }
    int ans=solve(getcentroid(1,0));
    cout<<(ans-1)<<endl;
    return 0;
}