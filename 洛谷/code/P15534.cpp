#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;

int a[MAXN];
int b[MAXN];

int q[MAXN][4];
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int cntq=1;

int fa[MAXN];
int son[MAXN];
int sz[MAXN];
int dep[MAXN];
int top[MAXN];
int dfncnt;
int dfn[MAXN];
int seg[MAXN];

int perm[MAXN];
int invperm[MAXN];

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

void write(int x){
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs1(int u,int f){
    sz[u]=1;
    dep[u]=dep[f]+1;
    fa[u]=f;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]]){
                son[u]=v;
            }
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}

void prepare(){
    dfs1(1,0);
    dfs2(1,1);
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        x=fa[top[x]];
    }
    return (dep[x]<dep[y])?x:y;
}

bool flag;

void change(int u){
    int x=a[u];
    int y=b[u];
    int px=invperm[x];
    int py=invperm[y];

    swap(perm[px],perm[py]);
    swap(invperm[x],invperm[y]);
}

inline void addedgeq(int u,int v){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    headq[u]=cntq++;
}

void dfs3(int u){
    change(u);

    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];

        int x=val[v];
        if(flag){
            val[v]=invperm[x];
        }
        else{
            val[v]=perm[x];
        }
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]){
            dfs3(v);
        }
    }
    change(u);
}

void run(int op,bool rev){
    for(int i=1;i<=n;i++){
        headq[i]=0;
    }
    cntq=1;

    for(int i=1;i<=m;i++){
        int u=q[i][op];
        if(u){
            addedgeq(u,i);
        }
    }

    for(int i=1;i<=n;i++){
        perm[i]=invperm[i]=i;
    }
    flag=rev;
    dfs3(1);
}

void compute(){
    run(0,true);
    run(3,false);
    run(2,true);
    run(1,false);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i++){
        b[i]=read();
    }

    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }

    prepare();

    for(int i=1;i<=m;i++){
        q[i][0]=read();
        q[i][1]=read();
        val[i]=read();
        q[i][2]=lca(q[i][0],q[i][1]);
        q[i][3]=fa[q[i][2]];
    }

    compute();

    for(int i=1;i<=m;i++){
        write(val[i]);
        putchar('\n');
    }
    return 0;
}