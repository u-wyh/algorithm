#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int MAXN = 1e5+5;

int n,m,k;
ull ALL;

struct Func{
    ull zero,one;
};

ull apply_func(Func &f,ull x){
    return (((~x)&f.zero)|(x&f.one))&ALL;
}

// 返回 g ∘ f，也就是先做 f，再做 g
Func compose(Func &g,Func &f){
    return {apply_func(g,f.zero),apply_func(g,f.one)};
}

// 恒等函数 F(x)=x
Func func_equal() {
    return {0, ALL};
}

Func make_func(int op,ull x){
    x&=ALL;
    if(op==1){
        return {0,x};
    }
    else if(op==2){
        return {x,ALL};
    }
    else{
        return {x,(~x)&ALL};
    }
}

struct node{
    Func lr,rl;
};

node merge_node(node &lt,node &rt){
    node res;
    res.lr=compose(rt.lr,lt.lr);
    res.rl=compose(lt.rl,rt.rl);
    return res;
}

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int opt[MAXN];
ull val[MAXN];

int fa[MAXN];
int sz[MAXN];
int son[MAXN];
int dep[MAXN];
int dfncnt;
int dfn[MAXN];
int seg[MAXN];
int top[MAXN];

node tree[MAXN<<2];

void dfs1(int u,int f){
    fa[u]=f;
    sz[u]=1;
    dep[u]=dep[f]+1;
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
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}

void build(int l,int r,int i){
    if(l==r){
        int x=seg[l];
        Func f=make_func(opt[x],val[x]);
        tree[i]={f,f};
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=merge_node(tree[i<<1],tree[i<<1|1]);
    }
}

void update(int pos,Func f,int l,int r,int i){
    if(l==r){
        tree[i]={f,f};
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,f,l,mid,i<<1);
        }
        else{
            update(pos,f,mid+1,r,i<<1|1);
        }
        tree[i]=merge_node(tree[i<<1],tree[i<<1|1]);
    }
}

node query(int ql,int qr,int l,int r,int i){
    if(ql<=l&&r<=qr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        if(ql<=mid&&qr>mid){
            node lt=query(ql,qr,l,mid,i<<1);
            node rt=query(ql,qr,mid+1,r,i<<1|1);
            return merge_node(lt,rt);
        }
        else if(ql>mid){
            return query(ql,qr,mid+1,r,i<<1|1);
        }
        else if(qr<=mid){
            return query(ql,qr,l,mid,i<<1);
        }
    }
}

Func query_path(int x,int y){
    Func lt=func_equal();
    Func rt=func_equal();

    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]){
            node now=query(dfn[top[x]],dfn[x],1,n,1);
            lt=compose(now.rl,lt);
            x=fa[top[x]];
        }
        else{
            node now=query(dfn[top[y]],dfn[y],1,n,1);
            rt=compose(rt,now.lr);
            y=fa[top[y]];
        }
    }
    if(dep[x]>=dep[y]){
        node now=query(dfn[y],dfn[x],1,n,1);
        lt=compose(now.rl,lt);
    }
    else{
        node now=query(dfn[x],dfn[y],1,n,1);
        lt=compose(now.lr,lt);
    }
    return compose(rt,lt);
}

ull compute(Func f,ull z){
    z&=ALL;

    bool ok[2]={0,1};
    ull dp[2]={0,0};

    for(int i=k-1;i>=0;i--){
        bool nok[2]={0,0};
        ull ndp[2]={0,0};

        for(int t=0;t<=1;t++){
            if(!ok[t]){
                continue;
            }
            int zbit=(z>>i)&1ull;
            int limit=t?zbit:1;
            for(int b=0;b<=limit;b++){
                int nt=t&&(b==zbit);
                ull out;
                if(b==0){
                    out=(f.zero>>i)&1ull;
                }
                else{
                    out=(f.one>>i)&1ull;
                }
                ull now=dp[t]|(out<<i);
                if(!nok[nt]||now>ndp[nt]){
                    nok[nt]=true;
                    ndp[nt]=now;
                }
            }
        }

        ok[0]=nok[0];
        ok[1]=nok[1];
        dp[0]=ndp[0];
        dp[1]=ndp[1];
    }

    ull ans=0;
    if(ok[0]){
        ans=max(ans,dp[0]);
    }
    if(ok[1]){
        ans=max(ans,dp[1]);
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;

    if(k==64){
        ALL=~0ull;
    }
    else{
        ALL=(1ull<<k)-1;
    }

    if(n==0){
        return 0;
    }

    for(int i=1;i<=n;i++){
        cin>>opt[i]>>val[i];
        val[i]&=ALL;
    }

    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        addedge(x,y);
        addedge(y,x);
    }

    dfs1(1,0);
    dfs2(1,1);

    build(1,n,1);

    for(int i=1;i<=m;i++){
        int Q,x,y;
        ull z;
        cin>>Q>>x>>y>>z;
        if(Q==1){
            Func f=query_path(x,y);
            cout<<compute(f,z)<<endl;
        }
        else{
            opt[x]=y;
            val[x]=z&ALL;
            Func f=make_func(opt[x],val[x]);
            update(dfn[x],f,1,n,1);
        }
    }
    return 0;
}