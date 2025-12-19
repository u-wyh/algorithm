//P2146
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int val[MAXN];
vector<int>vec[MAXN];

//链式前向星建图
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int tot=1;

//线段树
int tree[MAXN<<2];
int lazy[MAXN<<2];
int change[MAXN<<2];
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

int ans[MAXN];

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
}

//注意编号问题
void build(int l,int r,int i){
    lazy[i]=0;
    change[i]=-1;
    len[i]=r-l+1;
    if(l==r){
        tree[i]=val[rk[l]];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

bool check(int c,int lt,int rt){
    int l=0,r=vec[c].size()-1,ans=INT_MAX;
    while(l<=r){
        int mid=(l+r)/2;
        if(vec[c][mid]>=lt){
            ans=vec[c][mid];
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans<=rt;
}

inline bool sum(int x,int y,int v){
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        if(check(v,id[top[x]],id[x]))
            return true;
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    if(check(v,id[x],id[y]))
        return true;
    return false;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    for(int i=1;i<=n;i++){
        vec[val[i]].push_back(id[i]);
    }
    for(int i=1;i<=n;i++){
        //cout<<' '<<val[i]<<' '<<id[i]<<endl;
        sort(vec[i].begin(),vec[i].end());
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        if(sum(u,v,w)){
            cout<<1;
        }
        else{
            cout<<0;
        }
    }
    return 0;
}
