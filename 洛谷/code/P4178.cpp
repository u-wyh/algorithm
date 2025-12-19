#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;

int n,k;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

bool vis[MAXN];
int sz[MAXN];

int dis[MAXN];
int cnta;

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
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
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int d){
    if(d>k){
        return ;
    }
    dis[++cnta]=d;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,d+w);
        }
    }
}

int calc(int u,int d){
    cnta=0;
    dfs(u,0,d);
    int ans=0;
    sort(dis+1,dis+cnta+1);
    for(int l=1,r=cnta;l<=r;){
        if(dis[l]+dis[r]<=k){
            ans+=r-l;
            l++;
        }
        else{
            r--;
        }
    }
    return ans;
}

int compute(int u){
    vis[u]=true;
    int ans=calc(u,0);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!vis[v]){
            ans-=calc(v,w);
            ans+=compute(v);
        }
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    k=read();
    cout<<compute(getcentroid(1,0))<<endl;
    return 0;
}