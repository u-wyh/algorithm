#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e4+5;

int n,m;
int val[MAXN];

//链式前向星建图
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int tot=1;

//线段树
int tree[MAXN<<2];
int big[MAXN<<2];
int len[MAXN<<2];//要记录长度 因为这里加的话是每一个元素都要加

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

inline void addedge(int u,int v){
    Next[tot]=head[u];
    to[tot]=v;
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
}

//注意编号问题
void build(int l,int r,int i){
    len[i]=r-l+1;
    if(l==r){
        big[i]=tree[i]=val[rk[l]];
        //cout<<i<<  ": "<<l<<' '<<r<<' '<<tree[i]<<endl;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=big[i]=jobv;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
//    cout<<i<<": "<<l<<' '<<r<<' '<<jobl<<' '<<jobr<<endl;
//    system("pause");
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int querymax(int jobl,int jobr,int l,int r,int i){
//    cout<<i<<": "<<l<<' '<<r<<' '<<jobl<<' '<<jobr<<endl;
//    system("pause");

    if(jobl<=l&&r<=jobr){
        return big[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=LLONG_MIN;
        if(jobl<=mid){
            ans=max(ans,querymax(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,querymax(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

inline int sum(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ans+=query(id[top[x]],id[x],1,n,1);
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    ans+=query(id[x],id[y],1,n,1);
    return ans;
}

inline int qmax(int x,int y){
    //cout<<' '<<id[x]<<' '<<id[y]<<endl;
    int ans=LLONG_MIN;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ans=max(ans,querymax(id[top[x]],id[x],1,n,1));
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    ans=max(ans,querymax(id[x],id[y],1,n,1));
    return ans;
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
        cin>>val[i];
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    m=read();
    for(int i=1;i<=m;i++){
        string op;
        cin>>op;
        int u,v;
        u=read(),v=read();
        if(op=="CHANGE"){
            update(id[u],v,1,n,1);
        }
        else if(op=="QMAX"){
            cout<<qmax(u,v)<<endl;
        }
        else{
            cout<<sum(u,v)<<endl;
        }
    }
    return 0;
}

