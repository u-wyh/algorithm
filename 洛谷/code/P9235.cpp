#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 3e5+5;
const int LIMIT = 23;

int n,m,q;

struct node{
    int u,v,w;
};

int fa[MAXN<<1];
int key[MAXN<<1];
int cntg;

int head[MAXN<<1];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dep[MAXN<<1];
int st[MAXN<<1][LIMIT];

node nums[MAXM];

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

bool cmp(node a,node b){
    return a.w>b.w;
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int find(int i){
    return i==fa[i]?i:fa[i]=find(fa[i]);
}

void kruskalrebuild(){
    cntg=n;
    sort(nums+1,nums+m+1,cmp);
    for(int i=1;i<=m;i++){
        int u=nums[i].u;
        int v=nums[i].v;
        int fx=find(u);
        int fy=find(v);
        if(fx!=fy){
            fa[fx]=fa[fy]=++cntg;
            fa[cntg]=cntg;
            key[cntg]=nums[i].w;
            addedge(cntg,fx);
            addedge(cntg,fy);
        }
    }
}

void dfs(int u,int f){
    dep[u]=dep[f]+1;
    st[u][0]=f;
    for(int i=1;i<LIMIT;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        dfs(to[i],u);
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    for (int p = LIMIT - 1; p >= 0; p--) {
        if (dep[st[a][p]] >= dep[b]) {
            a = st[a][p];
        }
    }
    if (a == b) {
        return a;
    }
    for (int p = LIMIT - 1; p >= 0; p--) {
        if (st[a][p] != st[b][p]) {
            a = st[a][p];
            b = st[b][p];
        }
    }
    return st[a][0];
}

int main()
{
    n=read(),m=read(),q=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
    }
    kruskalrebuild();
    for(int i=n+1;i<=cntg;i++){
        if(i==find(i)){
            dfs(i,0);
        }
    }
    while(q--){
        int u,v;
        u=read(),v=read();
        if(find(u)!=find(v)){
            printf("-1\n");
        }
        else{
            printf("%d\n",key[lca(u,v)]);
        }
    }
    return 0;
}