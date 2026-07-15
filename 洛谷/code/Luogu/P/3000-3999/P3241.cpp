#include<bits/stdc++.h>
using namespace std;
const int MAXN = 150005;
const int MAXT = MAXN*40;

int n,q,h,m;
struct node{
    int val,pos;
};
node nums[MAXN];
int arr[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

int dfncnt;
int dep[MAXN];
int dfn[MAXN];
int seg[MAXN];
int son[MAXN];
int top[MAXN];
int fa[MAXN];
int sz[MAXN];
int dis[MAXN];
int d[MAXN];

int pre[MAXN];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
long long tree[MAXT];
long long addtag[MAXT];
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

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    fa[u]=f;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=f){
            dis[v]=dis[u]+w;
            d[v]=w;
            dfs1(v,u);
            sz[u]+=sz[v];
            if(son[u]==0||sz[son[u]]<sz[v]){
                son[u]=v;
            }
        }
    }
}

void dfs2(int u,int t){
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

int build(int l,int r){
    int rt=++cnt;
    if(l<r){
        int mid=(l+r)>>1;
        ls[rt]=build(l,mid);
        rs[rt]=build(mid+1,r);
    }
    return rt;
}

int find(int val){
    int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void prepare(){
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++){
        pre[i]=d[seg[i]];
    }
    for(int i=1;i<=n;i++){
        pre[i]+=pre[i-1];
    }
    for(int i=1;i<=n;i++){
        arr[i]=nums[i].val;
    }
    sort(arr+1,arr+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].val=find(nums[i].val);
    }
    root[0]=build(1,n);

}

int main()
{
    n=read(),q=read(),h=read();
    for(int i=1;i<=n;i++){
        nums[i].val=read();
        nums[i].pos=i;
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    prepare();
    return 0;
}