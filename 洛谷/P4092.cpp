//P4092
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int val[MAXN];

//链式前向星建图
int head[MAXN];
int Next[MAXN];
int to[MAXN];
int tot=1;

//线段树
int tree[MAXN<<2];
//int low[MAXN<<2];
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
    tree[i]=deep[tree[i<<1]]>deep[tree[i<<1|1]]?tree[i<<1]:tree[i<<1|1];
    //low[i]=deep[low[i<<1]]<deep[low[i<<1|1]]?low[i<<1]:low[i<<1|1];
}

//注意编号问题
void build(int l,int r,int i){
    len[i]=r-l+1;
    change[i]=0;
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

void updatelazy(int i,int v){
    if(deep[v]>deep[tree[i]]){
        change[i]=v;
        tree[i]=v;
        //low[i]=v;
    }
//    else if(deep[v]<=deep[low[i]]){
//        return ;
//    }
    else{
        updatelazy(i<<1,v);
        updatelazy(i<<1|1,v);
        up(i);
    }
}

void down(int i){
    if(change[i]!=0){
        updatelazy(i<<1,change[i]);
        updatelazy(i<<1|1,change[i]);
        change[i]=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        updatelazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
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

int query(int pos,int l,int r,int i){
    if(l==r){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        down(i);
        int ans=0;
        if(pos<=mid){
            ans=query(pos,l,mid,i<<1);
        }
        else{
            ans=query(pos,mid+1,r,i<<1|1);
        }
        return ans;
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
        val[i]=1;
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
//    cout<<endl;
//    for(int i=1;i<=n;i++){
//        cout<<id[i]<<' '<<sz[i]<<endl;
//    }
//    cout<<endl;
    for(int i=1;i<=m;i++){
        char op;
        int v;
        cin>>op;
        v=read();
        if(op=='C'){
            //cout<<v<<' '<<id[v]<<' '<<id[v]+sz[v]-1<<endl;
            update(id[v],id[v]+sz[v]-1,v,1,n,1);
        }
        else{
            cout<<query(v,1,n,1)<<endl;
        }
    }
    return 0;
}

/*
5 12
1 2
1 3
2 4
2 5
Q 2
Q 3
Q 1
Q 4
Q 5
C 4
C 2
Q 4
Q 2
Q 5
Q 3
Q 1
*/
