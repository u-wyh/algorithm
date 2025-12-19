#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXH = 20;
const int MAXT = MAXN*40;

int n,q,p;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

int dfn[MAXN];
int seg[MAXN];
int dfncnt;
int sz[MAXN];
int dep[MAXN];
int dis[MAXN];
int st[MAXN][MAXH];

int root[MAXN];
int tree[MAXT];
int ls[MAXT];
int rs[MAXT];
int cnt;

int lg2[MAXN];
int stmin[MAXN][MAXH];
int stmax[MAXN][MAXH];

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

void dfs(int u,int fa){
    sz[u]=1;
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa){
            dis[v]=dis[u]+w;
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
    // cout<<' '<<u<<' '<<sz[u]<<' '<<dis[u]<<endl;
}

inline int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
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
    if(l!=r){
        int mid=(l+r)>>1;
        ls[rt]=build(l,mid);
        rs[rt]=build(mid+1,r);
    }
    return rt;
}

int insert(int pos,int l,int r,int i){
    int rt=++cnt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    tree[rt]=tree[i]+1;
    if(l<r){
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=insert(pos,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(pos,mid+1,r,rs[rt]);
        }
    }
    return rt;
}

bool query(int jobl,int jobr,int l,int r,int u,int v){
    if(jobl<=l&&r<=jobr){
        if(tree[u]>tree[v]){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid&&jobr>mid){
            return (query(jobl,jobr,l,mid,ls[u],ls[v])||query(jobl,jobr,mid+1,r,rs[u],rs[v]));
        }
        else if(jobl<=mid){
            return query(jobl,jobr,l,mid,ls[u],ls[v]);
        }
        else{
            return query(jobl,jobr,mid+1,r,rs[u],rs[v]);
        }
    }   
}

void stbuild(){
    lg2[0]=-1;
    for(int i=1;i<=n;i++){
        lg2[i]=lg2[i>>1]+1;
        stmax[i][0]=dfn[i];
        stmin[i][0]=dfn[i];
    }
    for(int i=1;i<=lg2[n];i++){
        for(int j=1;j+(1<<(i-1))-1<=n;j++){
            stmax[j][i]=max(stmax[j][i-1],stmax[j+(1<<(i-1))][i-1]);
            stmin[j][i]=min(stmin[j][i-1],stmin[j+(1<<(i-1))][i-1]);
        }
    }
}

pair<int,int>query(int l,int r){
    int p=lg2[r-l+1];
    int maxans=max(stmax[l][p],stmax[r-(1<<p)+1][p]);
    int minans=min(stmin[l][p],stmin[r-(1<<p)+1][p]);
    return {maxans,minans};
}

void prepare(){
    root[0]=build(1,n);
    for(int i=1;i<=n;i++){
        root[i]=insert(seg[i],1,n,root[i-1]);
    }
    stbuild();
}

int findkth(int pos,int k){
    for(int i=p;i>=0;i--){
        if(k>=(1<<i)){
            k-=(1<<i);
            pos=st[pos][i];
        }
    }
    return pos;
}

int main()
{
    n=read(),q=read();
    p=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs(1,0);
    prepare();
    int lastans=0;
    for(int i=1;i<=q;i++){
        int pos,x,y;
        pos=read()^lastans;
        x=read()^lastans;
        y=read()^lastans;
        pair<int,int>maxmin=query(x,y);
        int lt=seg[maxmin.second],rt=seg[maxmin.first];
        int fa=lca(lt,rt);
        int ancestor=lca(fa,pos);
        int ans=0;
        if(ancestor==fa||ancestor==pos){
            if(ancestor==pos){
                ans=dis[fa]-dis[pos];
            }
            else{
                int l=dfn[pos],r=dfn[pos]+sz[pos]-1;
                bool flag=query(x,y,1,n,root[r],root[l-1]);
                if(flag){
                    ans=0;
                }
                else{
                    int left=1,right=dep[pos]-dep[ancestor],res=0;
                    while(left<=right){
                        int mid=(left+right)>>1;
                        int p=findkth(pos,mid);
                        l=dfn[p],r=dfn[p]+sz[p]-1;
                        if(query(x,y,1,n,root[r],root[l-1])){
                            res=mid;
                            right=mid-1;
                        }
                        else{
                            left=mid+1;
                        }
                    }
                    // cout<<' '<<findkth(pos,res)<<' '<<pos<<endl;
                    ans=dis[pos]-dis[findkth(pos,res)];
                }
            }
        }
        else{
            ans=dis[pos]+dis[fa]-2*dis[ancestor];
        }
        printf("%d\n",ans);
        lastans=ans;
    }
    return 0;
}
/*
5 4
3 1 2
1 5 1
2 3 3
3 4 4
2 3 5
2 1 7
0 7 7
5 5 2
*/