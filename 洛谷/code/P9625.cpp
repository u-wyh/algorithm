#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
const int MAXM=2e5+5;

// 原图每条边的两个端点
int eu[MAXM];
int ev[MAXM];

// 标记当前生成树包含的边
bool chosen[MAXM];

// 初始生成树邻接表
int head[MAXN];
int to[MAXN<<1];
int nxt[MAXN<<1];
int eid[MAXN<<1];
int cntg;

// 当前生成树中每个点的度数
int deg[MAXN];

// 并查集
int fa[MAXN];

// 遍历初始生成树使用的父亲和栈
int pa[MAXN];
int sta[MAXN];

// 每个集合当前保留的根边
int rootEdge[MAXN];

int n,m;
int limit;

int find(int x){
    int rt=x;

    while(fa[rt]!=rt){
        rt=fa[rt];
    }

    while(fa[x]!=x){
        int y=fa[x];
        fa[x]=rt;
        x=y;
    }

    return rt;
}

void addedge(int u,int v,int id){
    to[++cntg]=v;
    eid[cntg]=id;
    nxt[cntg]=head[u];
    head[u]=cntg;

    to[++cntg]=u;
    eid[cntg]=id;
    nxt[cntg]=head[v];
    head[v]=cntg;
}

// 任意构造一棵生成树
void buildTree(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }

    for(int i=1;i<=m;i++){
        int u=eu[i];
        int v=ev[i];

        if(u==v){
            continue;
        }

        int fu=find(u);
        int fv=find(v);

        if(fu==fv){
            continue;
        }

        fa[fu]=fv;
        chosen[i]=true;

        deg[u]++;
        deg[v]++;

        addedge(u,v,i);
    }
}

// 删除 rt 后，将它的每棵子树设为一个集合
void splitTree(int rt){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        pa[i]=0;
    }

    for(int i=head[rt];i;i=nxt[i]){
        int root=to[i];

        rootEdge[root]=eid[i];
        pa[root]=rt;

        int top=0;
        sta[++top]=root;

        while(top){
            int u=sta[top--];

            fa[u]=root;

            for(int j=head[u];j;j=nxt[j]){
                int v=to[j];

                if(v==pa[u]){
                    continue;
                }

                pa[v]=u;
                sta[++top]=v;
            }
        }
    }
}

// 判断加入 u-v 并删除 rt-root 后是否满足度数限制
bool valid(int u,int v,int root){
    int du=deg[u]+1-(u==root);
    int dv=deg[v]+1-(v==root);

    return du<=limit&&dv<=limit;
}

// 加入新边，并删除一个集合与 rt 相连的根边
void replaceEdge(int id,int u,int v,int root,int other,int rt){
    chosen[id]=true;
    chosen[rootEdge[root]]=false;

    deg[u]++;
    deg[v]++;
    deg[root]--;
    deg[rt]--;

    fa[root]=other;
}

void solve(){
    scanf("%d%d",&n,&m);

    limit=n/2;
    cntg=0;

    for(int i=1;i<=n;i++){
        head[i]=0;
        deg[i]=0;
        rootEdge[i]=0;
    }

    for(int i=1;i<=m;i++){
        scanf("%d%d",&eu[i],&ev[i]);
        chosen[i]=false;
    }

    buildTree();

    int rt=0;

    for(int i=1;i<=n;i++){
        if(deg[i]>limit){
            rt=i;
            break;
        }
    }

    if(rt){
        splitTree(rt);

        for(int i=1;i<=m&&deg[rt]>limit;i++){
            if(chosen[i]){
                continue;
            }

            int u=eu[i];
            int v=ev[i];

            if(u==v||u==rt||v==rt){
                continue;
            }

            int fu=find(u);
            int fv=find(v);

            if(fu==fv){
                continue;
            }

            if(valid(u,v,fu)){
                replaceEdge(i,u,v,fu,fv,rt);
            }
            else if(valid(u,v,fv)){
                replaceEdge(i,u,v,fv,fu,rt);
            }
        }
    }

    if(rt&&deg[rt]>limit){
        puts("No");
        return;
    }

    puts("Yes");

    for(int i=1;i<=m;i++){
        if(chosen[i]){
            printf("%d %d\n",eu[i],ev[i]);
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);

    while(T--){
        solve();
    }

    return 0;
}