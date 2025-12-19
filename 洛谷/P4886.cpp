#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int a[MAXN];
int b[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

bool vis[MAXN];
int siz[MAXN];

int tree[MAXN];
int dist[MAXN];

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

void getSize(int u, int fa) {
    siz[u] = 1;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (v != fa && !vis[v]) {
            getSize(v, u);
            siz[u] += siz[v];
        }
    }
}

int getCentroid(int u, int fa) {
    getSize(u, fa);
    int half = siz[u] >> 1;
    bool find = false;
    while (!find) {
        find = true;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v != fa && !vis[v] && siz[v] > half) {
                fa = u;
                u = v;
                find = false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int d,int rt){
    tree[u]=rt;
    dist[u]=d;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa){
            dfs(v,u,d+w,rt);
        }
    }
}

int compute(){
    int ans=INT_MAX;
    int u=getCentroid(1,0);
    while(!vis[u]){
        vis[u]=true;
        tree[u]=u;
        dist[u]=0;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            dfs(v,u,w,v);
        }
        int maxx=0,son=0;
        for(int i=1;i<=m;i++){
            int curdist=dist[a[i]]+dist[b[i]];
            int t1=tree[a[i]];
            int t2=tree[b[i]];
            if(maxx<curdist){
                maxx=curdist;
                if(t1!=t2){
                    son=0;
                }
                else{
                    son=t1;
                }
            }
            else if(maxx==curdist){
                if(t1!=t2||t1!=son){
                    son=0;
                }
            }
        }
        ans=min(ans,maxx);
        u=getCentroid(son,u);
    }
    return ans;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    for(int i=1;i<=m;i++){
        a[i]=read(),b[i]=read();
    }
    cout<<compute()<<endl;
    return 0;
}