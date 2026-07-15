#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m;
int val[MAXN];
struct node{
    int u,v;
}edge[MAXN];
int t;

//链式前向星建图
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int tot=1;

//线段树
int tree[MAXN<<2];
int lazy[MAXN<<2];
int big[MAXN<<2];
int small[MAXN<<2];

//树链剖分部分
int son[MAXN];//重儿子编号  叶子结点没有
int id[MAXN];//重新编号后的编号
int rk[MAXN];//重新编号后的编号对应原来的编号是什么
int cnt;
int fa[MAXN];//父亲节点编号
int deep[MAXN];//节点深度
int sz[MAXN];//以该节点为首的子树节点总数
int top[MAXN];//这条重链的头结点

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
    Next[tot]=head[u];
    to[tot]=v;
    weight[tot]=w;
    head[u]=tot++;
}

//第一遍dfs 完成sz、deep、fa、son数组的统计
void dfs1(int u,int f){
    fa[u]=f;
    deep[u]=deep[f]+1;
    sz[u]=1;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        val[v]=weight[i];
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
}

//第二遍dfs 完成top、rk、id
void dfs2(int u,int t){
    top[u]=t;
    id[u]=++cnt;
    rk[cnt]=u;
    if(son[u]){
        //存在重儿子  优先遍历
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
            //另外在开一条重链
        }
    }
}

//线段树部分
void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
    big[i]=max(big[i<<1],big[i<<1|1]);
    small[i]=min(small[i<<1],small[i<<1|1]);
}

//注意编号问题
void build(int l,int r,int i){
    lazy[i]=1;
    if(l==r){
        big[i]=small[i]=tree[i]=val[rk[l]];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
    //cout<<i<<": "<<l<<' '<<r<<' '<<tree[i]<<endl;
}

void downlazy(int i,int v){
    tree[i]*=-1;
    lazy[i]*=-1;
    int tmp=big[i];
    big[i]=small[i]*-1;
    small[i]=-1*tmp;
}

void down(int i){
    if(lazy[i]!=1){
        downlazy(i<<1,-1);
        downlazy(i<<1|1,-1);
        lazy[i]=1;
    }
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        big[i]=small[i]=tree[i]=jobv;
        lazy[i]=1;
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void mul(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        downlazy(i,-1);
    }
    else{
        down(i);
        int mid=(l+r)/2;
        if(jobl<=mid){
            mul(jobl,jobr,l,mid,i<<1);
        }
        else{
            mul(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int querymin(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr){
        return INT_MAX;
    }
    if(jobl<=l&&r<=jobr){
        return small[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=INT_MAX;
        if(jobl<=mid){
            ans=min(ans,querymin(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,querymin(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

int querymax(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr){
        return INT_MIN;
    }
    if(jobl<=l&&r<=jobr){
        return big[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=INT_MIN;
        if(jobl<=mid){
            ans=max(ans,querymax(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,querymax(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

int querysum(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=0;
        if(jobl<=mid){
            ans+=querysum(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=querysum(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

inline int qsum(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ans+=querysum(id[top[x]],id[x],1,n,1);
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    ans+=querysum(id[x]+1,id[y],1,n,1);
    return ans;
}

inline int qmin(int x,int y){
    int ans=INT_MAX;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ans=min(ans,querymin(id[top[x]],id[x],1,n,1));
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    ans=min(ans,querymin(id[x]+1,id[y],1,n,1));
    return ans;
}

inline int qmax(int x,int y){
    int ans=INT_MIN;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ans=max(ans,querymax(id[top[x]],id[x],1,n,1));
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    ans=max(ans,querymax(id[x]+1,id[y],1,n,1));
    return ans;
}

inline void mul(int x,int y){
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        mul(id[top[x]],id[x],1,n,1);
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    mul(id[x]+1,id[y],1,n,1);
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        u++,v++;
        addedge(u,v,w);
        addedge(v,u,w);
        edge[i].u=u;
        edge[i].v=v;
    }
    m=read();
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    for(int i=1;i<=m;i++){
        string op;
        int u,v;
        cin>>op;
        u=read(),v=read();
        if(op=="C"){
            int a=edge[u].u,b=edge[u].v;
            if(deep[a]>deep[b]){
                update(id[a],v,1,n,1);
            }
            else{
                update(id[b],v,1,n,1);
            }
        }
        else{
            u++,v++;
            if(op=="N"){
                mul(u,v);
            }
            else if(op=="SUM"){
                cout<<qsum(u,v)<<endl;
            }
            else if(op=="MAX"){
                cout<<qmax(u,v)<<endl;
            }
            else{
                cout<<qmin(u,v)<<endl;
            }
        }
    }
    return 0;
}

