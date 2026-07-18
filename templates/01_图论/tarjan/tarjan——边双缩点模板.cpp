// https://www.luogu.com.cn/problem/P18867
//这道题实际上是一个树形dp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MAXM = 1e6+5;
const int MOD = 1e9+7;

int n,m;

int p[MAXM+MAXN];

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

//边双缩点后的边
int head1[MAXN];
int nxt1[MAXM<<1];
int to1[MAXM<<1];
int cnt1=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int st[MAXN];
bool instack[MAXN];
int top;
int color;
int col[MAXN];

int e[MAXN];//表示这个联通块内部有多少边
int b[MAXN];//表示这个联通块为首的子树有多少边
int v[MAXN];//这个联通块内部有多少个点

int f[MAXN][2];//在以u为首的子树上  f[u][0]表示无军营，f[u][1]表示有军营  并且子树上的所有点都可以到达u
int ans;

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void Addedge(int u,int v){
    nxt1[cnt1]=head1[u];
    to1[cnt1]=v;
    head1[u]=cnt1++;
}

//边双缩点其实和强连通分量缩点是一样的  这种写法更简洁  
void tarjan(int u,int fa){
    dfn[u]=low[u]=++dfncnt;
    instack[u]=true;
    st[++top]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[v],low[u]);
        }
        else if(instack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        col[u]=++color;
        instack[u]=false;
        v[color]++;
        while(st[top]!=u){
            int to=st[top];
            instack[to]=false;
            col[to]=color;
            v[color]++;
            top--;
        }
        top--;
    }
}

void dfs1(int u,int fa){
    b[u]=e[u];// 双连通分量内部的边数
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        b[u]+=b[v]+1;//子树以及桥边
    }
}

void dfs2(int u,int fa){
    f[u][0]=p[e[u]];// 不建造军营的方案数
    f[u][1]=(p[v[u]+e[u]]-p[e[u]]+MOD)%MOD;
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(v==fa){
            continue;
        }
        dfs2(v,u);
        //记录旧状态
        int tmp0=f[u][0],tmp1=f[u][1];
        //如果子树中有值  那么自己可以有值 也可以没有值
        //如果自己没有  那么儿子就得有  那么这条中间边（桥）只有一种选择  就是必须连 因为必须要和u一起
        //如果自己有  那么儿子如果没有的话  中间的边可以连  也可以不连   儿子有的话  必须连
        f[u][1]=(tmp0*f[v][1]%MOD+tmp1*((2*f[v][0])%MOD+f[v][1])%MOD)%MOD;
        //子树中没有值  那么中间边可以有  也可以没有
        f[u][0]=(tmp0*2*f[v][0]%MOD)%MOD;
    }

    //这个统计答案的逻辑很独特  就是枚举所有的树都在某一个子树里面   并且这颗子树一定无法到达外界
    //这样就和我们的条件设定相符合（f[u][1]表示子树中所有有值的点都一定可以到达u）  使得统计答案时不会出错
    if(u==col[1]){
        // 根节点（1号节点所在的双连通分量）
        ans=(ans+f[u][1])%MOD;
    }
    else{
        // 非根节点：乘上子树外边的方案数  并且和上级相连的边一定不能选
        ans=(ans+f[u][1]*p[b[col[1]]-b[u]-1])%MOD;
    }
}

signed main()
{
    n=read(),m=read();
    p[0]=1;
    for(int i=1;i<=n+m;i++){
        p[i]=(p[i-1]*2)%MOD;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    tarjan(1,0);
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(col[u]==col[v]){
                e[col[u]]++;
            }
            else{
                Addedge(col[u],col[v]);//注意这里是单向边  因为原来的边是双向的  所以反边也一定会访问到
            }
        }
    }
    for(int i=1;i<=color;i++){
        e[i]/=2;//边被计算了两次  所以要除以2
    }

    // 计算子树总边数 
    dfs1(col[1],0);
    //树形dp
    dfs2(col[1],0);

    cout<<ans<<endl;
    return 0;
}