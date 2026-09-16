#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,q;
int root;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;
int deg[MAXN];

int son[MAXN];
int fa[MAXN];
int sz[MAXN];
int dfncnt;
int dfn[MAXN];
int seg[MAXN];
int top[MAXN];
int leafsum[MAXN];
int childcnt[MAXN];

int len[MAXN<<2];
int tag[MAXN<<2];
int odd[MAXN<<2]; 

int arr[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
    deg[v]++;
}

void dfs1(int u,int f){
    sz[u]=1;
    fa[u]=f;
    leafsum[u]=(deg[u]==1)?1:0;
    childcnt[u]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
            childcnt[u]++;
            leafsum[u]+=leafsum[v];
            if(sz[v]>sz[son[u]]){
                son[u]=v;
            }
        }
    }
}

void dfs2(int u,int t){
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    top[u]=t;
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

void up(int x){
    odd[x]=odd[x<<1]+odd[x<<1|1];
}

void build(int l,int r,int i){
    len[i]=r-l+1;
    tag[i]=0;
    if(l==r){
        if(seg[l]!=root)
            odd[i]=leafsum[seg[l]]%2;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void prepare(){
    root=1;
    while(deg[root]==1){
        root++;
    }
    dfs1(root,0);
    dfs2(root,root);

    build(1,n,1);
}

void lazy(int i){
    odd[i]=len[i]-odd[i];
    tag[i]^=1;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1);
        lazy(i<<1|1);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void changepath(int u){
    while(top[u]!=top[root]){
        update(dfn[top[u]],dfn[u],1,n,1);
        u=fa[top[u]];
    }
    if(u!=root){
        update(dfn[root]+1,dfn[u],1,n,1);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    prepare();

    int baseleaves=leafsum[root];
    for(int i=1;i<=q;i++){
        int d;
        cin>>d;
        int leaves=baseleaves;
        for(int i=1;i<=d;i++){
            int x;
            cin>>x;
            arr[i]=x;

            if(childcnt[x]>0){
                changepath(x);
                leaves++;
            }
            childcnt[x]++;
        }
        if(leaves&1){
            cout<<-1<<endl;
        }
        else{
            long long ans=2ll*(n-1)-odd[1]+d;
            cout<<ans<<endl;
        }

        for(int i=d;i>=1;i--){
            int x=arr[i];
            childcnt[x]--;
            if(childcnt[x]>0){
                changepath(x);
            }
        }
    }
    return 0;
}