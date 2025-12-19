#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int INF = 1e9;

int n,m;
bool bomb[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int f[MAXN];
int g[MAXN];
int cnt;

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
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int fa,int mid){
    f[u]=-INF;
    g[u]=INF;

    if(bomb[u]){
        f[u]=0;
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u,mid);
            f[u]=max(f[u],f[v]+1);
            g[u]=min(g[u],g[v]+1);
        }
    }

    if(g[u]+f[u]<=mid){
        f[u]=-INF;
    }
    if(f[u]==mid){
        cnt++;
        f[u]=-INF;
        g[u]=0;
    }
}

bool check(int mid){
    cnt=0;
    dfs(1,0,mid);
    if(f[1]>=0){
        cnt++;
    }
    return cnt<=m;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        bomb[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    int l=0,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}