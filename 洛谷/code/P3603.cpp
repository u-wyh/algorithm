#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 405;
const int MAXV = 3e4+5;

int n,m,f;
int arr[MAXN];
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int fa[MAXN];
int son[MAXN];
int sz[MAXN];
int dep[MAXN];
int top[MAXN];
int dfn[MAXN];
int dfncnt;

int blen,bnum;
int bi[MAXN];
int bl[MAXM];
int br[MAXM];
bitset<MAXV>bit[MAXM];

bitset<MAXV>ans;

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u,int f){
    fa[u]=f;
    dep[u]=dep[f]+1;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        dfs1(v,u);
        sz[u]+=sz[v];
        if(!son[u]||sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    val[dfncnt]=arr[u];
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa[u]||v==son[u]){
            continue;
        }
        dfs2(v,v);
    }
}

void prepare(){
    dfs1(1,0);
    dfs2(1,1);
    blen=sqrt(n*20);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(i*blen,n);
        for(int j=bl[i];j<=br[i];j++){
            bit[i][val[j]]=1;
        }
    }
}

void query(int l,int r){
    if (bi[l] == bi[r]) {
        for (int i = l; i <= r; i++) {
            ans[val[i]] = 1;
        }
    } else {
        for (int i = l; i <= br[bi[l]]; i++) {
            ans[val[i]] = 1;
        }
        for (int i = bl[bi[r]]; i <= r; i++) {
            ans[val[i]] = 1;
        }
        for (int i = bi[l] + 1; i <= bi[r] - 1; i++) {
            ans |= bit[i];
        }
    }
}

void update(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        query(dfn[top[x]],dfn[x]);
        x=fa[top[x]];
    }
    query(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]));
}

int main()
{
    n=read(),m=read(),f=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    prepare();
    int lastans=0;
    for(int i=1;i<=m;i++){
        ans.reset();
        int k=read();
        for(int j=1;j<=k;j++){
            int x,y;
            x=read(),y=read();
            if(f){
                x^=lastans;
                y^=lastans;
            }
            update(x,y);
        }
        int ans1=ans.count();
        int ans2=MAXV;
        for(int i=0;i<MAXV;i++){
            if(ans[i]==0){
                ans2=i;
                break;
            }
        }
        printf("%d %d\n",ans1,ans2);
        lastans=ans1+ans2;
    }
    return 0;
}