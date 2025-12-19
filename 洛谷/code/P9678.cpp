#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 1e6+5;
const int MAXP = MAXN*2*20;
const long long INF = 1ll<<60;

int n,m;

struct Query{
    int x,y,id;
};
Query query[MAXM];

struct Pair{
    int a,b;
    long long d;
};
Pair pairarr[MAXP];
int cntp;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

bool vis[MAXN];
int sz[MAXN];

long long dist[MAXN];
int node[MAXN];
int cnta;

int sta[MAXN];
int top;

long long tree[MAXN<<2];
long long ans[MAXM];

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

void getsize(int u, int fa) {
    sz[u] = 1;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (v != fa && !vis[v]) {
            getsize(v, u);
            sz[u] += sz[v];
        }
    }
}

int getCentroid(int u, int fa) {
    getsize(u, fa);
    int half = sz[u] >> 1;
    bool find = false;
    while (!find) {
        find = true;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v != fa && !vis[v] && sz[v] > half) {
                fa = u;
                u = v;
                find = false;
                break;
            }
        }
    }
    return u;
}

bool cmp(Query &a,Query &b){
    return a.y<b.y;
}

bool cmp1(Pair &a,Pair &b){
    return a.b<b.b;
}

void dfs(int u,int fa,long long dis){
    dist[u]=dis;
    node[++cnta]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,dis+w);
        }
    }
}

void stackadd(int cur){
    while(top>0&&dist[sta[top]]>=dist[cur]){
        pairarr[++cntp]={min(sta[top],cur),max(sta[top],cur),dist[sta[top]]+dist[cur]};
        top--;
    }
    sta[++top]=cur;
}

void calc(int u){
    cnta=0;
    dfs(u,0,0);
    sort(node+1,node+cnta+1);
    top=0;
    for(int i=1;i<=cnta;i++){
        stackadd(node[i]);
    }
    top=0;
    for(int i=cnta;i>=1;i--){
        stackadd(node[i]);
    }
}

void solve(int u){
    vis[u]=true;
    calc(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            solve(getCentroid(v,u));
        }
    }
}

void build(int l,int r,int i){
    tree[i]=INF;
    if(l<r){
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void update(int pos,long long jobv,int l,int r,int i){
    if(l==r){
        tree[i]=min(tree[i],jobv);
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        tree[i]=min(tree[i<<1],tree[i<<1|1]);
    }
}

long long querymin(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        long long ans=INF;
        if(jobl<=mid){
            ans=min(ans,querymin(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,querymin(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

void compute(){
    solve(getCentroid(1,0));
    sort(query+1,query+m+1,cmp);
    sort(pairarr+1,pairarr+cntp+1,cmp1);
    build(1,n,1);
    for(int i=1,j=1;i<=m;i++){
        for(;j<=cntp&&pairarr[j].b<=query[i].y;j++){
            update(pairarr[j].a,pairarr[j].d,1,n,1);
        }
        if(query[i].x==query[i].y){
            ans[query[i].id]=-1;
        }
        else{
            ans[query[i].id]=querymin(query[i].x,query[i].y,1,n,1);
        }
    }
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
    m=read();
    for(int i=1;i<=m;i++){
        query[i].x=read();
        query[i].y=read();
        query[i].id=i;
    }
    compute();
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}