#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e3+5;
const int MAXM = 1e4+2e3+5;

int n,m;
int limit[MAXN];
int in[MAXN];
// int fa[MAXN];
int ans[MAXN];
bool vis[MAXN];

int fa[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

int headg[MAXN];
int nxtg[MAXM];
int tog[MAXM];
int cntg=1;

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
    in[v]++;
}

inline void addedgeg(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

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

void dfs(int u){
    if(vis[u]){
        return ;
    }
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        // fa[v]=u;
        dfs(v);
        limit[u]=min(limit[u],limit[v]-1);
    }
}

void dfs2(int u,int op){
    if(vis[u]==op){
        return ;
    }
    vis[u]=op;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        dfs2(v,op);
    }
}

bool cmp(int a,int b){
    return limit[a]<limit[b];
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        limit[i]=read();
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedgeg(v,u);
    }
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            addedge(n+1,i);
        }
    }
    dfs(n+1);

    for(int i=1;i<=n;i++){
        ans[i]=i;
    }
    sort(ans+1,ans+n+1,cmp);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    cout<<endl;

    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<limit[i]<<' ';
    // }
    // cout<<endl;

    for(int i=1;i<=n;i++){
        vis[i]=false;
    }
    for(int i=1;i<=n;i++){
        // int tmp=i;
        // while(tmp!=(n+1)){
        //     vis[tmp]=true;
        //     tmp=fa[tmp];
        // }
        dfs2(i,1);
        for(int x=1;x<=n;x++){
            fa[x]=x;
        }
        for(int j=n;j>=1;j--){
            if(vis[ans[j]]){
                continue;
            }
            int x=find(limit[ans[j]]);
            fa[x]=x-1;
        }
        for(int x=n;x>=1;x--){
            if(x==find(x)){
                cout<<x<<' ';
                break;
            }
        }
        dfs2(i,0);
        // tmp=i;
        // while(tmp!=(n+1)){
        //     vis[tmp]=false;
        //     tmp=fa[tmp];
        // }
    }
    return 0;
}