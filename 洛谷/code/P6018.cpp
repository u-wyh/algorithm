#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXH = 22;
const int MAXK = 2e7+5;

int n,m;
int val[MAXN];

int dfn[MAXN];
int seg[MAXN];
int dfncnt;
int lt[MAXN];
int rt[MAXN];
int sz[MAXN];
int fa[MAXN];

int cnt;
int root[MAXN];
int trie[MAXK][2];
int pass[MAXK];
int one[MAXN][MAXH];

int tree[MAXN<<2];
int tag[MAXN<<2];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

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

void insert(int val,int u){
    int cur=root[u];
    pass[cur]++;
    for(int i=0;i<=19;i++){
        int path=(val>>i)&1;
        if(path){
            one[u][i]++;
        }
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
        pass[cur]++;
    }
}

void del(int val,int u){
    int cur=root[u];
    pass[cur]--;
    for(int i=0;i<=19;i++){
        int path=(val>>i)&1;
        if(path){
            one[u][i]--;
        }
        cur=trie[cur][path];
        pass[cur]--;
    }
}

void addone(int u,int cur,int d){
    if(cur==0||pass[cur]==0||d>19){
        return ;
    }
    one[u][d]+=pass[trie[cur][0]]-pass[trie[cur][1]];
    swap(trie[cur][0],trie[cur][1]);
    addone(u,trie[cur][0],d+1);
}

void dfs(int u,int f){
    lt[u]=dfncnt+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            fa[v]=u;
            dfn[v]=++dfncnt;
            seg[dfncnt]=v;
            insert(val[v],u);
        }
    }
    rt[u]=dfncnt;
    sz[u]=rt[u]-lt[u]+1;

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=val[seg[l]];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void lazy(int i,int val){
    tag[i]+=val;
    tree[i]+=val;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void add(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,1);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

void update(int pos,int val,int l,int r,int i){
    if(l==r){
        tree[i]=val;
    }
    else{
        down(i);
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,val,l,mid,i<<1);
        }
        else{
            update(pos,val,mid+1,r,i<<1|1);
        }
    }
}

int query(int pos,int l,int r,int i){
    if(l==r){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(pos<=mid){
            return query(pos,l,mid,i<<1);
        }
        else{
            return query(pos,mid+1,r,i<<1|1);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }

    for(int i=1;i<=n;i++){
        root[i]=++cnt;
    }
    dfn[1]=++dfncnt;
    seg[dfncnt]=1;
    dfs(1,0);
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,x,v;
        op=read(),x=read();
        if(op==2){
            v=read();
            int old=query(dfn[x],1,n,1);
            int now=old-v;
            if(fa[x]){
                del(old,fa[x]);
                insert(now,fa[x]);
            }
            update(dfn[x],now,1,n,1);
        }
        else{
            if(op==1){
                addone(x,root[x],0);
                if(fa[x]){
                    add(dfn[fa[x]],dfn[fa[x]],1,n,1);
                }
                if(sz[x]){
                    add(lt[x],rt[x],1,n,1);
                }
                if(fa[fa[x]]){
                    int old=query(dfn[fa[x]],1,n,1)-1;
                    del(old,fa[fa[x]]);
                    insert(old+1,fa[fa[x]]);
                }
            }
            else{
                int ans=0;
                for(int p=0;p<=19;p++){
                    if(one[x][p]&1){
                        ans+=(1<<p);
                    }
                }
                if(fa[x]){
                    ans^=query(dfn[fa[x]],1,n,1);
                }
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}