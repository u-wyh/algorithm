#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;

int n;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

int sz[MAXN];
bool vis[MAXN];

int all[MAXN];
int cur[MAXN];

int gcd(int a,int b){
    return (b==0)?a:gcd(b,a%b);
}

void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa||vis[v]){
            continue;
        }
        getsize(v,u);
        sz[u]+=sz[v];
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
            if(v!=fa&&!vis[v]&&sz[v]>=half){
                find=false;
                fa=u;
                u=v;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int dis){
    cur[dis%3]++;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!vis[v]&&v!=fa){
            dfs(v,u,dis+w);
        }
    }
}

int calc(int u){
    int ans=1;
    all[0]=1;
    all[1]=all[2]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!vis[v]){
            cur[0]=cur[1]=cur[2]=0;
            dfs(v,u,w);
            ans+=all[0]*cur[0]*2+all[1]*cur[2]*2+all[2]*cur[1]*2;
            all[0]+=cur[0];
            all[1]+=cur[1];
            all[2]+=cur[2];
        }
    }
    return ans;
}

int solve(int u){
    int ans=0;
    vis[u]=true;
    ans+=calc(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            ans+=solve(getcentroid(v,u));
        }
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        addedge(u,v,w);
        addedge(v,u,w);
    }
    int centroid=getcentroid(1,0);
    int a=solve(centroid);
    int b=n*n;
    int c=gcd(a,b);
    a/=c;
    b/=c;
    cout<<a<<"/"<<b<<endl;
    return 0;
}