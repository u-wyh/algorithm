#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXH = 21;
const int MAXK = MAXN*2;

int n,q;

struct edge{
    int u,v,w;
}nums[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];

int cntk=1;
int headk[MAXK];
int nxtk[MAXK];
int tok[MAXK];
int key[MAXK];
int cntu;

int fa[MAXK];
int dep[MAXK];
int st[MAXK][MAXH];

int dfncnt;
int seg[MAXN];
int dfn[MAXN];
int treemin[MAXN<<2];
int treemax[MAXN<<2];
int maxx[MAXN<<2];
int minn[MAXN<<2];
int tag[MAXN<<2];

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

bool cmp(edge a,edge b){
    return a.w<b.w;
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

inline void addEdge(int u,int v){
    nxtk[cntk]=headk[u];
    tok[cntk]=v;
    headk[u]=cntk++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void kruskalRebuild(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    cntu=n;
    for(int i=1;i<n;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
            
        cntu++;
        fa[fx]=cntu;
        fa[fy]=cntu;
        fa[cntu]=cntu;
        key[cntu]=nums[i].w;
        addEdge(cntu,fx);
        addEdge(cntu,fy);
        
    }
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<MAXH;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=headk[u];i;i=nxtk[i]){
        int v=tok[i];
        dfs(v,u);
    }
    if(u<=n){
        dfn[u]=++dfncnt;
        seg[dfncnt]=u;
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=MAXH-1;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=MAXH-1;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

void up(int i){
    treemin[i]=min(treemin[i<<1],treemin[i<<1|1]);
    treemax[i]=max(treemax[i<<1],treemax[i<<1|1]);
}

void build(int l,int r,int i){
    tag[i]=0;
    if(l==r){
        treemax[i]=INT_MIN;
        treemin[i]=INT_MAX;
        maxx[i]=minn[i]=dfn[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        treemax[i]=INT_MIN;
        treemin[i]=INT_MAX;
        maxx[i]=max(maxx[i<<1],maxx[i<<1|1]);
        minn[i]=min(minn[i<<1],minn[i<<1|1]);
    }
}

void lazy(int i,int op){
    tag[i]=op;
    if(op==1){
        treemin[i]=minn[i];
        treemax[i]=maxx[i];
    }
    else{
        treemax[i]=INT_MIN;
        treemin[i]=INT_MAX;
    }
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int l,int r,int i,int op){
    if(jobl<=l&&r<=jobr){
        lazy(i,op);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,l,mid,i<<1,op);
        }
        if(jobr>mid){
            update(jobl,jobr,mid+1,r,i<<1|1,op);
        }
        up(i);
    }
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
        nums[i].u=u;
        nums[i].v=v;
        nums[i].w=w;
    }
    sort(nums+1,nums+n,cmp);
    kruskalRebuild();
    dfs(cntu,0);
    build(1,n,1);
    while(q--){
        int op,u,v;
        op=read(),u=read();
        if(op==3){
            if(treemin[1]==INT_MAX||(treemin[1]==treemax[1]&&treemin[1]==dfn[u])){
                printf("-1\n");
            }
            else{
                int l=seg[min(treemin[1],dfn[u])];
                int r=seg[max(treemax[1],dfn[u])];
                printf("%d\n",key[lca(l,r)]);
            }
        }
        else{
            v=read();
            update(u,v,1,n,1,op);
        }
    }
    return 0;
}