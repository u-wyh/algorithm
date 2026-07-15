#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXH = 21;
const int MAXM = MAXN*25;

int n,q,origin,p;

int sta[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int dfncnt;
int dfn[MAXN];
int dep[MAXN];
int sz[MAXN];
int son[MAXN];
int top[MAXN];
int st[MAXN][MAXH];

int root[MAXN];
int ls[MAXM];
int rs[MAXM];
int sum[MAXM];
int cnt;

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
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

inline int lca(int a,int b){
    if(dep[a]<dep[b]) swap(a,b);
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b) return a;
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int build(int l,int r){
    int rt=++cnt;
    if(l<r){
        int mid=(l+r)>>1;
        ls[rt]=build(l,mid);
        rs[rt]=build(mid+1,r);
    }
    return rt;
}

void dfs1(int u,int fa){
    st[u][0]=fa;
    dep[u]=dep[fa]+1;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v,u);
        sz[u]+=sz[v];
        if(son[u]==0||sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=st[u][0]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}

void prepare(){
    dfs1(origin,0);
    dfs2(origin,origin);
    root[0]=build(1,n);
}

int update(int pos,int l,int r,int i){
    int rt=++cnt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    sum[rt]=sum[i]+1;
    if(l<r){
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=update(pos,l,mid,ls[rt]);
        }
        else{
            rs[rt]=update(pos,mid+1,r,rs[rt]);
        }
    }
    return rt;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[i]);
        }
        return ans;
    }
}

int query(int x,int y,int i){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        ans+=query(dfn[top[x]],dfn[x],1,n,i);
        x=st[top[x]][0];
    }
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    ans+=query(dfn[y],dfn[x],1,n,i);
    return ans;
}

int main()
{
    n=read();
    p=log2(n)+1;
    for(int i=1;i<=n;i++){
        int u=read();
        if(u==0){
            origin=i;
        }
        else{
            addedge(u,i);
        }
    }

    prepare();

    q=read();
    for(int i=1;i<=q;i++){
        int op=read();
        if(op==1){
            root[i]=root[i-1];
            int x,y,c;
            x=read(),y=read(),c=read();
            int ans1=dep[x]+dep[y]-dep[lca(x,y)]*2+1;
            int ans2=0;
            if(i-c-1<0){
                ans2=0;
            }
            else{
                ans2=query(x,y,root[i-c-1]);
            }
            printf("%d %d\n",ans1,ans2);
        }
        else{
            int t=read();
            if(sta[dfn[t]]==0){
                root[i]=update(dfn[t],1,n,root[i-1]);
                sta[dfn[t]]=1;
            }
        }
    }
    return 0;
}