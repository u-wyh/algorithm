#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXH = 22;

int n,m,p;

struct Edge{
    int u,v;
};
Edge edge[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

bool vis[MAXN];

int dep[MAXN];
int st[MAXN][MAXH];
int fa[MAXN];
int edgeid[MAXN];
int ans[MAXN];

int node[MAXN];
int nodecnt;

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

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        edgeid[v]=weight[i];
        dfs(v,u);
    }
}

inline int lca(int x,int y){
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[x][i]]>=dep[y]){
            x=st[x][i];
        }
    }
    if(x==y){
        return x;
    }
    for(int i=p;i>=0;i--){
        if(st[x][i]!=st[y][i]){
            x=st[x][i];
            y=st[y][i];
        }
    }
    return st[x][0];
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(dep[fx]>dep[fy]){
            swap(fx,fy);
        }
        fa[fy]=fx;
    }
}

void compute(int now,int goal){
    now=find(now);
    while(dep[now]>dep[goal]){
        node[++nodecnt]=edgeid[now];
        un(now,st[now][0]);
        now=find(st[now][0]);
    }
}

int main()
{
    n=read(),m=read();
    p=log2(n)+1;
    for(int i=1;i<=m;i++){
        edge[i].u=read();
        edge[i].v=read();
    }
    for(int i=1;i<n;i++){
        int id=read();
        vis[id]=true;
        addedge(edge[id].u,edge[id].v,id);
        addedge(edge[id].v,edge[id].u,id);
    }
    dfs(1,0);
    // for(int i=1;i<=n;i++){
    //     cout<<i<<":  "<<edgeid[i]<<endl;
    // }
    // cout<<endl;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    int now=0;
    for(int i=1;i<=m;i++){
        if(ans[i]){
            continue;
        }
        if(vis[i]){
            ans[i]=++now;
            un(edge[i].u,edge[i].v);
        }
        else{
            int fa=lca(edge[i].u,edge[i].v);
            // cout<<i<<":  "<<edge[i].u<<' '<<edge[i].v<<' '<<fa<<endl;
            nodecnt=0;
            compute(edge[i].u,fa);
            compute(edge[i].v,fa);

            sort(node+1,node+nodecnt+1);
            for(int k=1;k<=nodecnt;k++){
                int id=node[k];
                // cout<<' '<<id;
                if(!ans[id]){
                    ans[id]=++now;
                }
            }
            // cout<<endl;
            ans[i]=++now;
        }
    }

    for(int i=1;i<=m;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}