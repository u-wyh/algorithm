#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MOD = 1e9+7;

int n;
struct node{
    int val,id;
}nums[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int fa[MAXN];
int sz[MAXN];
int dep[MAXN];
int son[MAXN];
int dfn[MAXN];
int seg[MAXN];
int top[MAXN];
int dfncnt;

int tree[MAXN<<2];
int len[MAXN<<2];
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

bool cmp(node a,node b){
    return a.val>b.val;
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
        if(son[u]==0||sz[son[u]]<sz[v]){
            son[u]=v;
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
	tree[i]=(tree[i<<1]+tree[i<<1|1])%MOD;
}

void build(int l,int r,int i){
	len[i]=r-l+1;
	if(l==r){
		tree[i]=sz[seg[l]];
	}
	else{
		int mid=(l+r)>>1;
		build(l,mid,i<<1);
		build(mid+1,r,i<<1|1);
		up(i);
	}
}

void lazy(int i,int v){
	tag[i]+=v;
	tree[i]+=len[i]*v;
}

void down(int i){
	if(tag[i]){
		lazy(i<<1,tag[i]);
		lazy(i<<1|1,tag[i]);
		tag[i]=0;
	}
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
	if(jobl<=l&&r<=jobr){
		lazy(i,jobv);
	}
	else{
		int mid=(l+r)>>1;
		down(i);
		if(jobl<=mid){
			add(jobl,jobr,jobv,l,mid,i<<1);
		}
		if(jobr>mid){
			add(jobl,jobr,jobv,mid+1,r,i<<1|1);
		}
		up(i);
	}
}

int query(int jobl,int jobr,int l,int r,int i){
	if(jobl<=l&&r<=jobr){
		return tree[i];
	}
	else{
		int mid=(l+r)>>1;
		down(i);
		int ans=0;
		if(jobl<=mid){
			ans+=query(jobl,jobr,l,mid,i<<1);
		}
		if(jobr>mid){
			ans+=query(jobl,jobr,mid+1,r,i<<1|1);
		}
		return ans%MOD;
	}
}

int querypath(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            swap(x,y);
        }
        ans=(ans+query(dfn[top[x]],dfn[x],1,n,1))%MOD;
        x=fa[top[x]];
    }
    ans=(ans+query(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),1,n,1))%MOD;
    return ans;
}

void addpath(int x,int y,int val){
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            swap(x,y);
        }
        add(dfn[top[x]],dfn[x],val,1,n,1);
        x=fa[top[x]];
    }
    add(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),val,1,n,1);
}

signed main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        nums[i].val=read();
        nums[i].id=i;
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    sort(nums+1,nums+n+1,cmp);
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+querypath(1,nums[i].id)*nums[i].val%MOD)%MOD;
        addpath(1,nums[i].id,-1);
    }
    ans=(ans%MOD+MOD)%MOD;
    printf("%lld\n",ans);
    return 0;
}