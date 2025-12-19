#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int MAXH = 20;

int n,m,d;
int initedge;
long long initans;

struct Edge{
    int u,v,w,id;
    bool okay;
};
Edge edge[MAXM];

int fa[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int id[MAXN<<1];
int cnt=1;

int dep[MAXN];
int st[MAXN][MAXH];
int stfa[MAXN][MAXH];
int lg2[MAXN];

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

bool cmp(Edge &a,Edge &b){
    return (a.w==b.w)?(a.id<b.id):(a.w<b.w);
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void addedge(int u,int v,int i){
    nxt[cnt]=head[u];
    to[cnt]=v;
    id[cnt]=i;
    head[u]=cnt++;
}

void MST(){
    for(int i=1;i<=m;i++){
        int fx=find(edge[i].u);
        int fy=find(edge[i].v);
        if(fx!=fy){
            edge[i].okay=true;
            if(edge[i].id<n){
                initedge++;
            }
            initans+=edge[i].w;
            fa[fx]=fy;
            addedge(edge[i].u,edge[i].v,i);
            addedge(edge[i].v,edge[i].u,i);
        }
    }
}

// 边权相同 尽可能用编号更大的  这样可以尽可能保证不是最初的n-1条边
int maxval(int x,int y){
    if(edge[x].w!=edge[y].w){
        return (edge[x].w>edge[y].w)?x:y;
    }
    return max(x,y);
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    stfa[u][0]=fa;
    for(int i=1;i<=lg2[n];i++){
        stfa[u][i]=stfa[stfa[u][i-1]][i-1];
        st[u][i]=maxval(st[u][i-1],st[stfa[u][i-1]][i-1]);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            st[v][0]=id[i];
            dfs(v,u);
        }
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=lg2[n];i>=0;i--){
        if(dep[stfa[a][i]]>=dep[b]){
            a=stfa[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=lg2[n];i>=0;i--){
        if(stfa[a][i]!=stfa[b][i]){
            a=stfa[a][i];
            b=stfa[b][i];
        }
    }
    return stfa[a][0];
}

int querymax(int u,int top){
    int ans=0;
    for(int i=lg2[n];i>=0;i--){
        if(dep[stfa[u][i]]>=dep[top]){
            ans=maxval(ans,st[u][i]);
            u=stfa[u][i];
        }
    }
    return ans;
}

int main()
{
    n=read(),m=read(),d=read();
    for(int i=1;i<=m;i++){
        edge[i].u=read();
        edge[i].v=read();
        edge[i].w=read();
        edge[i].id=i;
    }
    sort(edge+1,edge+m+1,cmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    MST();
    lg2[0]=-1;
    for(int i=1;i<=n;i++){
        lg2[i]=lg2[i>>1]+1;
    }
    dfs(1,0);
    long long ans=LLONG_MAX;
    int edgecnt=n-1;
    for(int i=1;i<=m;i++){
        if(edge[i].okay){
            if(ans>initans-min(d,edge[i].w)){
                ans=initans-min(d,edge[i].w);
                edgecnt=initedge;
            }
            else if(ans==(initans-min(d,edge[i].w))){
                edgecnt=max(edgecnt,initedge);
            }
        }
        else{
            int u=edge[i].u;
            int v=edge[i].v;
            int uvlca=lca(u,v);
            int maxid=maxval(querymax(u,uvlca),querymax(v,uvlca));
            if(ans>(initans-edge[maxid].w+max(0,edge[i].w-d))){
                ans=(initans-edge[maxid].w+max(0,edge[i].w-d));
                edgecnt=initedge+(edge[i].id<n?1:0)-(edge[maxid].id<n?1:0);
            }
            else if(ans==(initans-edge[maxid].w+max(0,edge[i].w-d))){
                edgecnt=max(edgecnt,initedge+(edge[i].id<n?1:0)-(edge[maxid].id<n?1:0));
            }
        }
    }
    cout<<(n-1-edgecnt)<<endl;
    return 0;
}