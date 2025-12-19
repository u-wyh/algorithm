#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXH = 21;

int n,m,p;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

int dep[MAXN];
long long dist[MAXN];
int dfn[MAXN];
int seg[MAXN];
int st[MAXN][MAXH];
int dfncnt;

int arr[MAXN];
bool treasure[MAXN];

set<int>s;
set<int>::iterator it;

long long ans[MAXN];

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
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa){
            dist[v]=dist[u]+w;
            dfs(v,u);
        }
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

long long getdist(int x,int y){ // 改为 long long
    return 1ll*dist[x]+1ll*dist[y]-2ll*dist[lca(x,y)];
}

void compute(){
    long long curans=0;
    for(int i=1;i<=m;i++){
        int node=arr[i];
        int dfnid=dfn[node];
        if(!treasure[node]){
            s.insert(dfnid);
        }
        else{
            s.erase(dfnid);
        }
        treasure[node]=!treasure[node];

        if(s.size()<=1){
            curans=0;
        }
        else{
            int low=seg[(it=s.lower_bound(dfnid))==s.begin()?*--s.end():*--it];
            int high=seg[(it=s.upper_bound(dfnid))==s.end()?*s.begin():*it];

            long long delta=getdist(node,low)+getdist(node,high)-getdist(low,high);
            if(treasure[node]){
                curans+=delta;
            }
            else{
                curans-=delta;
            }
        }
        ans[i]=curans;
    }
}

int main()
{
    n=read(),m=read();
    p=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        arr[i]=read();
    }
    compute();
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}