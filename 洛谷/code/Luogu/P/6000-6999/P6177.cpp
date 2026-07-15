#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;
const int MAXM = 205;

int n,m;
int arr[MAXN];
int tot=1;
int sorted[MAXN];
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int fa[MAXN];
int dep[MAXN];
int sz[MAXN];
int son[MAXN];
int top[MAXN];
int dfn[MAXN];
int dfncnt;

int blen,bnum;
int bi[MAXN];
int bl[MAXM];
int br[MAXM];
bitset<MAXN>bit[MAXM];

bitset<MAXN>ans;

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

int find(int v){
    int l=1,r=tot,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=v){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
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
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
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
    if(bi[l]==bi[r]){
        for(int i=l;i<=r;i++){
            ans[val[i]]=1;
        }
    }
    else{
        for(int i=l;i<=br[bi[l]];i++){
            ans[val[i]]=1;
        }
        for(int i=bl[bi[r]];i<=r;i++){
            ans[val[i]]=1;
        }
        for(int i=bi[l]+1;i<=bi[r]-1;i++){
            ans|=bit[i];
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
    if(dep[x]>dep[y]){
        swap(x,y);
    }
    query(dfn[x],dfn[y]);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        sorted[i]=arr[i];
    }

    sort(sorted+1,sorted+n+1);
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++tot]=sorted[i];
        }
    }
    for(int i=1;i<=n;i++){
        arr[i]=find(arr[i]);
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
        int u,v;
        u=read(),v=read();
        u^=lastans;
        update(u,v);
        lastans=ans.count();
        printf("%d\n",lastans);
    }
    return 0;
}