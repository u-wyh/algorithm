#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m;
int val[MAXN];

int dfncnt1;
int fa[MAXN];
int dfn1[MAXN];
int rk1[MAXN];
int sz[MAXN];
int son[MAXN];//记录每个节点的儿子中最小的dfn序号

int dfncnt;
int dfn[MAXN];
int siz[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];

int tree[MAXN<<2];
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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int f){
    fa[u]=f;
    son[u]=dfncnt1+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        sz[u]++;
        dfn1[v]=++dfncnt1;
        rk1[dfncnt1]=v;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        dfs(v,u);
    }
}

void dfs1(int u,int fa){
    siz[u]=1;
    dfn[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        siz[u]+=siz[v];
    }
}

void build(int l,int r,int i){
    tag[i]=0;
    if(l==r){
        tree[i]=val[rk1[l]];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void lazy(int i,int v){
    tree[i]+=v;
    tag[i]+=v;
}

void down(int i){
    if(tag[i]!=0){
        lazy(i<<1,-tag[i]);
        lazy(i<<1|1,-tag[i]);
        tag[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    // cout<<jobl<<' '<<jobr<<' '<<l<<' '<<r<<' '<<i<<endl;
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
}

pair<int,int> query(int pos,int l,int r,int i){
    // cout<<pos<<' '<<l<<' '<<r<<endl;
    if(l==r){
        return {tree[i],tag[i]};
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(pos<=mid){
            return query(pos,l,mid,i<<1);
        }
        else{
            return query(pos,mid+1,r,i<<1|1);
        }
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v),addedge(v,u);
    }
    dfn1[1]=++dfncnt1;
    rk1[dfncnt1]=1;
    dfs(1,0);
    dfs1(1,0);
    // for(int i=1;i<=n;i++){
    //     cout<<i<<": "<<fa[i]<<' '<<dfn1[i]<<' '<<sz[i]<<' '<<son[i]<<' '<<dfn[i]<<' '<<siz[i]<<endl;
    // }
    build(1,n,1);
    // for(int i=1;i<=n;i++){
    //     cout<<rk1[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<i<<' '<<query(dfn1[i],1,n,1).first<<endl;
    // }
    for(int i=1;i<=m;i++){
        int op,u,v;
        op=read(),u=read();
        if(op==1){
            v=read();
            add(dfn1[u],dfn1[u],v,1,n,1);
        }
        else{
            v=1;
            while(v!=u){
                pair<int,int>tmp=query(dfn1[v],1,n,1);
                add(son[v],son[v]+sz[v]-1,-tmp.second,1,n,1);
                for(int ei=head[v];ei;ei=nxt[ei]){
                    int k=to[ei];
                    if(k!=fa[v]&&(siz[k]+dfn[k]-1)>=dfn[u]&&dfn[k]<=dfn[u]){
                        v=k;
                        break;
                    }
                }
            }
            printf("%lld\n",query(dfn1[v],1,n,1).first);
        }
    }
    return 0;
}