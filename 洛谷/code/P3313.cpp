#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXC = 1e5+5;
const int MAXT = 2e6+5;

int n,m;

int val[MAXN];
int kind[MAXN];

int root[MAXC];
int maxx[MAXT];
int sum[MAXT];
int ls[MAXT];
int rs[MAXT];
int cnt;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dep[MAXN];
int dfncnt;
int dfn[MAXN];
int seg[MAXN];
int sz[MAXN];
int son[MAXN];
int fa[MAXN];
int top[MAXN];

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

void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    fa[u]=f;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            if(son[u]==0||sz[son[u]]<sz[v]){
                son[u]=v;
            }
            sz[u]+=sz[v];
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
        if(v==fa[u]||v==son[u]){
            continue;
        }
        dfs2(v,v);
    }
}

void up(int i){
    maxx[i]=max(maxx[ls[i]],maxx[rs[i]]);
    sum[i]=sum[ls[i]]+sum[rs[i]];
}

void update(int pos,int val,int l,int r,int i){
    if(l==r){
        maxx[i]=val;
        sum[i]=val;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            if(ls[i]==0){
                ls[i]=++cnt;
            }
            update(pos,val,l,mid,ls[i]);
        }
        else{
            if(rs[i]==0){
                rs[i]=++cnt;
            }
            update(pos,val,mid+1,r,rs[i]);
        }
        up(i);
    }
}

int querymax(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return maxx[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            if(ls[i]){
                ans=max(ans,querymax(jobl,jobr,l,mid,ls[i]));
            }
        }
        if(jobr>mid){
            if(rs[i]){
                ans=max(ans,querymax(jobl,jobr,mid+1,r,rs[i]));
            }
        }
        return ans;
    }
}

int querysum(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            if(ls[i]){
                ans+=querysum(jobl,jobr,l,mid,ls[i]);
            }
        }
        if(jobr>mid){
            if(rs[i]){
                ans+=querysum(jobl,jobr,mid+1,r,rs[i]);
            }
        }
        return ans;
    }
}

int pathmax(int x,int y,int c){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            ans=max(ans,querymax(dfn[top[y]],dfn[y],1,n,root[c]));
            y=fa[top[y]];
        }
        else{
            ans=max(ans,querymax(dfn[top[x]],dfn[x],1,n,root[c]));
            x=fa[top[x]];
        }
    }
    ans=max(ans,querymax(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),1,n,root[c]));
    return ans;
}

int pathsum(int x,int y,int c){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            ans+=querysum(dfn[top[y]],dfn[y],1,n,root[c]);
            y=fa[top[y]];
        }
        else{
            ans+=querysum(dfn[top[x]],dfn[x],1,n,root[c]);
            x=fa[top[x]];
        }
    }
    ans+=querysum(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),1,n,root[c]);
    return ans;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        kind[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    // for(int i=1;i<=n;i++){
    //     cout<<i<<": "<<dfn[i]<<' '<<sz[i]<<' '<<son[i]<<' '<<fa[i]<<' '<<kind[i]<<' '<<val[i]<<endl;
    // }
    for(int i=1;i<=n;i++){
        if(root[kind[i]]==0){
            root[kind[i]]=++cnt;
        }
        update(dfn[i],val[i],1,n,root[kind[i]]);
    }
    for(int i=1;i<=m;i++){
        char op[3];
        int u,v;
        scanf("%s",op);
        u=read(),v=read();
        if(op[1]=='C'){
            update(dfn[u],0,1,n,root[kind[u]]);
            kind[u]=v;
            if(root[v]==0){
                root[v]=++cnt;
            }
            update(dfn[u],val[u],1,n,root[v]);
        }
        else if(op[1]=='W'){
            update(dfn[u],v,1,n,root[kind[u]]);
            val[u]=v;
        }
        else if(op[1]=='S'){
            printf("%d\n",pathsum(u,v,kind[u]));
        }
        else{
            printf("%d\n",pathmax(u,v,kind[u]));
        }
    }
    return 0;
}