#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;
const int MAXM = 1e5+5;
const int LIMIT = 16;

int n,m,k;

int sta[MAXN];
int top=0;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

int col[MAXN];
int color;
vector<int> ans[MAXN]; // 存储每个点双的节点
bool cut[MAXN];

int dep[MAXN];
int st[MAXN][LIMIT];

int cnt=1;
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];

int tot=1;
int head1[MAXN];
int nxt1[MAXM<<1];
int to1[MAXM<<1];

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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void addEdge(int u,int v){
    nxt1[tot]=head1[u];
    to1[tot]=v;
    head1[u]=tot++;
}

void tarjan(int u, int f){
    dfn[u] = low[u] = ++dfncnt; 
    sta[++top] = u;           
    int child = 0;           

    for(int i = head[u]; i; i=nxt[i]){
        int v = to[i];
        if(!dfn[v]){          // 如果v未被访问
            child++;
            tarjan(v, u);     // 递归访问v
            low[u] = min(low[u], low[v]); // 更新low[u]
            if(low[v] >= dfn[u]){
                cut[u]=true;
                color++;      // 新的点双编号
                while(sta[top+1] != v){ 
                    ans[color].push_back(sta[top--]);
                }
                ans[color].push_back(u); // 割点u属于当前点双
            }
        }
        else if(v != f){     
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<LIMIT;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

inline int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=LIMIT-1;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=LIMIT-1;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

inline int dist(int u,int v){
    int fa=lca(u,v);
    return (dep[u]+dep[v]-dep[fa]*2);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    tarjan(1,0);
    m=color;
    for(int i=1;i<=n;i++){
        if(cut[i]){
            col[i]=++m;
        }
    }
    for(int i=1;i<=color;i++){
        for(int j=0;j<(int)ans[i].size();j++){
            int v=ans[i][j];
            if(cut[v]){
                addEdge(i,col[v]),addEdge(col[v],i);
            }
            else{
                col[v]=i;
            }
        }
    }
    dfs(1,0);
    k=read();
    for(int i=1;i<=k;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        u=col[u],v=col[v];
        if(u==v||!cut[w]){
            cout<<"no"<<endl;
            continue;
        }
        w=col[w];
        if(dist(u,w)+dist(v,w)==dist(u,v)){
            cout<<"yes"<<endl;
        }
        else{
            cout<<"no"<<endl;
        }
    }
    return 0;
}