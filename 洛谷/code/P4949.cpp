#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+10;

int n,m;
int val[MAXN];
struct node{
    int u,v,w;
}edge[MAXN];

//链式前向星建图
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int tot=1;

//线段树
int tree[MAXN<<2];

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
        val[v]=weight[i];//这里变化
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
inline void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
}

//注意编号问题
void build(int l,int r,int i){
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

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=jobv;
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
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
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
    ans-=query(id[x],id[x],1,n,1);
    return ans;
}

int main()
{
    n=read(),m=read();
    edge[n].u=read(),edge[n].v=read(),edge[n].w=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
        edge[i].u=u,edge[i].v=v,edge[i].w=w;
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,u,v;
        op=read(),u=read(),v=read();
        if(op==1){
            if(u==1){
                edge[n].w=v;
            }
            else{
                u--;
                if(deep[edge[u].u]>deep[edge[u].v]){
                    update(id[edge[u].u],v,1,n,1);
                }
                else{
                    update(id[edge[u].v],v,1,n,1);
                }
            }
        }
        else{
            int ans1=sum(u,v);
            int ans2=sum(u,edge[n].u)+edge[n].w+sum(v,edge[n].v);
            int ans3=sum(v,edge[n].u)+edge[n].w+sum(u,edge[n].v);
            cout<<min(min(ans1,ans2),ans3)<<endl;
        }
    }
    return 0;
}
