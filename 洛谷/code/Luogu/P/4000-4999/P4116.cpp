//P2146
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int val[MAXN];

set<int>ans[MAXN];

//链式前向星建图
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int tot=1;

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

int main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=m;i++){
        int op,u;
        op=read(),u=read();
        if(op==0){
            val[u]^=1;
            if(val[u]==1){
                ans[top[u]].insert(id[u]);
            }
            else{
                ans[top[u]].erase(id[u]);
            }
        }
        else{
            int res=INT_MAX;
            while(u){
                if(ans[top[u]].size()){
                    int v=*ans[top[u]].begin();
                    if(deep[rk[v]]<=deep[u]){
                        res=rk[v];
                    }
                }
                u=fa[top[u]];
            }
            if(res==INT_MAX){
                res=-1;
            }
            cout<<res<<endl;
        }
    }
    return 0;
}

