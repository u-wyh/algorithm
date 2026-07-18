#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;

// 表示每个操作之后的答案
int ans[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int fa[MAXN];
int son[MAXN];
int sz[MAXN];
int top[MAXN];
int dep[MAXN];
int dfncnt;
int dfn[MAXN];
int seg[MAXN];

// 表示某个点第一次被染成黑色的时间
int first[MAXN];

// 表示从位置i开始之后，第一个没有染色的位置
int father[MAXN];

bool okay[MAXN];
int dial[MAXN];
int diar[MAXN];
int dia[MAXN];

int maxlen;

struct node{
    int x;
    int t;
};
node nums[MAXN];

bool cmp(node &a,node &b){
    return a.t<b.t;
}

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
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

void clear(){
    for(int i=1;i<=n;i++){
        head[i]=0;
        son[i]=0;
    }
    cntg=1;
    dfncnt=0;
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
            if(sz[son[u]]<sz[v]){
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
        if(v!=son[u]&&v!=fa[u]){
            dfs2(v,v);
        }
    }
}

void prepare(){
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n+1;i++){
        father[i]=i;
        first[i]=m+1;
    }
}

int find(int x){
    return x==father[x]?x:father[x]=find(father[x]);
}

void calc(int x,int y,int t){
    for(int i=find(x);i<=y;i=find(i+1)){
        father[i]=i+1;
        first[i]=t;
    }
}

void pathcalc(int x,int y,int t){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        calc(dfn[top[x]],dfn[x],t);
        x=fa[top[x]];
    }
    calc(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),t);
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        x=fa[top[x]];
    }
    return dfn[x]<dfn[y]?x:y;
}

void func(int x,int y,int u){
    int xylca=lca(x,y);
    int len=dep[x]+dep[y]-2*dep[xylca]+1;
    if(len>dia[u]){
        dia[u]=len;
        dial[u]=x;
        diar[u]=y;
    }
}

void un(int x,int y){
    x=find(x);
    y=find(y);
    if(x!=y){
        father[x]=y;
        int l1=dial[x];
        int r1=diar[x];
        int l2=dial[y];
        int r2=diar[y];

        func(l1,r1,y);
        func(l1,r2,y);
        func(l1,l2,y);
        func(r1,r2,y);
        func(r1,l2,y);
    }
}

void activate(int u){
    okay[u]=true;

    dial[u]=diar[u]=u;
    dia[u]=1;

    maxlen=max(maxlen,dia[u]);

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(okay[v]){
            v=find(v);
            un(u,v);
            maxlen=max(maxlen,dia[v]);
        }
    }
}

void compute(){
    for(int i=1;i<=n;i++){
        nums[i]={i,first[dfn[i]]};
    }
    sort(nums+1,nums+n+1,cmp);

    // 先处理黑色部分
    for(int i=1;i<=n;i++){
        father[i]=i;
        okay[i]=false;
    }
    maxlen=0;
    int lt=0,rt=n;
    for(int i=1;i<=m;i++){
        while(lt+1<=n&&nums[lt+1].t==i){
            lt++;
            activate(nums[lt].x);
        }
        ans[i]=maxlen;
    }

    // 处理白色部分
    for(int i=1;i<=n;i++){
        father[i]=i;
        okay[i]=false;
    }
    maxlen=0;
    for(int i=m+1;i>=2;i--){
        // 这里多一个m+1  不会影响答案 但是可以统一代码
        while(rt>=1&&nums[rt].t==i){
            activate(nums[rt].x);
            rt--;
        }
        ans[i-1]=max(ans[i-1],maxlen);
    }
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        clear();

        for(int i=1;i<n;i++){
            int u,v;
            u=read(),v=read();
            addedge(u,v);
            addedge(v,u);
        }

        prepare();

        for(int i=1;i<=m;i++){
            int u,v;
            u=read(),v=read();
            pathcalc(u,v,i);
        }

        compute();

        for(int i=1;i<=m;i++){
            write(ans[i]);
            putchar('\n');
        }
    }
    return 0;
}