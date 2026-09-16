#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int colcnt;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int fa[MAXN];
int son[MAXN];
int sz[MAXN];
int dfn[MAXN];
int seg[MAXN];
int top[MAXN];
int dep[MAXN];
int dfncnt;

struct node{
    int cnt;
    int lcol;
    int rcol;
    int lazy;
};
node nums[MAXN<<2];

void prepare(){
    for(int i=1;i<=n;i++){
        head[i]=0;
        son[i]=0;
    }
    cntg=1;
    dfncnt=0;
    colcnt=n;
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
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    top[u]=t;
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

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        x=fa[top[x]];
    }
    return dep[x]>dep[y]?y:x;
}

void up(int x){
    nums[x].cnt=nums[x<<1].cnt+nums[x<<1|1].cnt;
    nums[x].lcol=nums[x<<1].lcol;
    nums[x].rcol=nums[x<<1|1].rcol;
    nums[x].cnt-=((nums[x<<1].rcol==nums[x<<1|1].lcol)?1:0);
}

void build(int l,int r,int i){
    if(l==r){
        nums[i]={1,seg[l],seg[l],0};
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
    nums[i].lazy=0;
}

void updatelazy(int x,int v){
    nums[x]={1,v,v,v};
}

void down(int x){
    if(nums[x].lazy){
        updatelazy(x<<1,nums[x].lazy);
        updatelazy(x<<1|1,nums[x].lazy);
        nums[x].lazy=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        updatelazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

node merge(node ls,node rs){
    return {ls.cnt+rs.cnt-((ls.rcol==rs.lcol)?1:0),ls.lcol,rs.rcol,0};
}

node reverse(node x){
    swap(x.lcol,x.rcol);
    return x;
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return nums[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid&&jobr>mid){
            return merge(query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobl<=mid){
            return query(jobl,jobr,l,mid,i<<1);
        }
        else{
            return query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

void pathupdate(int x,int y){
    ++colcnt;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        update(dfn[top[x]],dfn[x],colcnt,1,n,1);
        x=fa[top[x]];
    }
    update(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),colcnt,1,n,1);
}

int pathquery(int x,int y){
    node lt={0,0,0,0};
    node rt={0,0,0,0};

    int len=0;

    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]){
            node cur=query(dfn[top[x]],dfn[x],1,n,1);
            cur=reverse(cur);
            lt=merge(lt,cur);

            len+=dfn[x]-dfn[top[x]]+1;
            x=fa[top[x]];
        }
        else{
            node cur=query(dfn[top[y]],dfn[y],1,n,1);
            rt=merge(cur,rt);
            
            len+=dfn[y]-dfn[top[y]]+1;
            y=fa[top[y]];
        }
    }

    if(dep[x]<dep[y]){
        node cur=query(dfn[x],dfn[y],1,n,1);
        rt=merge(cur,rt);
        len+=dfn[y]-dfn[x]+1;
    }
    else{
        node cur=query(dfn[y],dfn[x],1,n,1);
        cur=reverse(cur);
        lt=merge(lt,cur);
        len+=dfn[x]-dfn[y]+1;
    }
    node all=merge(lt,rt);
    return len-all.cnt;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        prepare();
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }

        dfs1(1,0);
        dfs2(1,1);
        build(1,n,1);

        for(int i=1;i<=m;i++){
            int op,x,y;
            cin>>op>>x>>y;
            if(op==1){
                pathupdate(x,y);
            }
            else{
                cout<<pathquery(x,y)<<endl;
            }
        }
    }
    return 0;
}