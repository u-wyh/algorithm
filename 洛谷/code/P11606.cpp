#include<bits/stdc++.h>
using namespace std;

const int MAXN=1005;
const int MAXM=10005;

int n,m;

// T限制构成的无向图
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cntg=1;

// 每个点被要求位于哪些点的下面
int inhead[MAXN];
int innxt[MAXM];
int into[MAXM];
int cntin=1;

// 每个点不能成为哪些点的祖先
int nohead[MAXN];
int nonxt[MAXM];
int noto[MAXM];
int cntno=1;

// 当前递归区间中的点
int ord[MAXN];
int tmp[MAXN];
int que[MAXN];

// 每个连通块在ord中的右端点
int bound[MAXN];

// 当前点集和搜索标记
int belong[MAXN];
int vis[MAXN];
int tim;

// 最终构造出的父亲
int father[MAXN];

void addgraph(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void addin(int u,int v){
    innxt[cntin]=inhead[u];
    into[cntin]=v;
    inhead[u]=cntin++;
}

void addno(int u,int v){
    nonxt[cntno]=nohead[u];
    noto[cntno]=v;
    nohead[u]=cntno++;
}

bool canroot(int u,int id){
    // u不能有当前点集中的必选祖先
    for(int i=inhead[u];i;i=innxt[i]){
        if(belong[into[i]]==id){
            return false;
        }
    }

    // u成为根后会成为其余所有点的祖先
    for(int i=nohead[u];i;i=nonxt[i]){
        if(belong[noto[i]]==id){
            return false;
        }
    }

    return true;
}

bool build(int l,int r,int pa){
    int id=++tim;

    for(int i=l;i<=r;i++){
        belong[ord[i]]=id;
    }

    // 寻找当前子树的根
    int root=0;

    for(int i=l;i<=r;i++){
        if(canroot(ord[i],id)){
            root=ord[i];
            break;
        }
    }

    if(root==0){
        return false;
    }

    father[root]=pa;

    // 删除当前根
    belong[root]=0;

    // 按T限制的无向连通块重新排列剩余节点
    int write=l;

    for(int i=l;i<=r;i++){
        int s=ord[i];

        if(s==root||vis[s]==id){
            continue;
        }

        int start=write;
        int ql=1;
        int qr=1;

        que[1]=s;
        vis[s]=id;

        while(ql<=qr){
            int u=que[ql++];

            tmp[write++]=u;

            for(int j=head[u];j;j=nxt[j]){
                int v=to[j];

                if(belong[v]==id&&vis[v]!=id){
                    vis[v]=id;
                    que[++qr]=v;
                }
            }
        }

        bound[start]=write-1;
    }

    for(int i=l;i<write;i++){
        ord[i]=tmp[i];
    }

    // 每个连通块作为root的一棵儿子子树
    int pos=l;

    while(pos<write){
        int end=bound[pos];

        if(!build(pos,end,root)){
            return false;
        }

        pos=end+1;
    }

    return true;
}

int main(){
    scanf("%d%d",&n,&m);

    for(int i=1;i<=n;i++){
        ord[i]=i;
    }

    for(int i=1;i<=m;i++){
        int x,y;
        char c;

        scanf("%d%d %c",&x,&y,&c);

        if(c=='T'){
            // y必须是x的祖先
            addgraph(x,y);
            addgraph(y,x);

            // x存在必选祖先y
            addin(x,y);
        }else{
            // y不能是x的祖先
            addno(y,x);
        }
    }

    if(!build(1,n,0)){
        printf("NIE\n");
        return 0;
    }

    for(int i=1;i<=n;i++){
        printf("%d\n",father[i]);
    }

    return 0;
}