// https://www.luogu.com.cn/problem/P7924
// 题意：给定 n 个点 m 条边的无向连通图（无重边自环），
// 第 i 个点美观度为 a_i。
// 定义旅游路径为两点间边不重复（点可重复）的路径。
// 共 q 次询问，每次指定两个顶点 x, y，走遍 x 到 y 的所有旅游路径。
// 求 q 次询问走过的所有点的并集（重复经过同一顶点只计一次）的美观度之和。
// 输入 n, m，n 个 a_i，m 条边，q 及 q 组 (x, y)。
// 输出一行一个整数。
// 数据范围：
// 3 <= n <= 5*10^5，m <= 2*10^6，q <= 10^6，
// 1 <= a_i <= 100，图连通且无重边自环。
// 算法标签：边双连通分量、最近公共祖先、树上差分
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 2e6+5;
const int LIMIT = 20;

int n,m;
int val[MAXN];
int ans=0;
int diff[MAXN];

int p;
int dep[MAXN];
int st[MAXN][LIMIT];

int col[MAXN];
int color;
int sum[MAXN];
queue<int>q;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
bool vis[MAXM<<1];
bool bridge[MAXM<<1];
int cnt=1;

int head1[MAXN];
int nxt1[MAXM<<1];
int to1[MAXM<<1];
int cnt1=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

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

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        if(vis[i]){
            continue;
        }
        vis[i]=vis[((i-1)^1)+1]=true;
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]){
                bridge[i]=bridge[((i-1)^1)+1]=true;
            }
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }
}

void dfs(int u,int fa){
    // diff[u]=diff[fa]+sum[u];
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
    }
}

int lca(int a,int b){
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

// int lca(int x,int y){
//     if(dep[x]<dep[y]) 
//         swap(x,y);
//     int t=dep[x]-dep[y];
//     for(int i=p;i>=0;--i)
//         if(t&(1<<i))
//             x=st[x][i];
//     if(x==y) 
//         return x;
//     for(int i=p;i>=0;--i)
//         if(st[x][i]!=st[y][i]) 
//             x=st[x][i],y=st[y][i];
//     return st[x][0];
// }

void dfs1(int u,int fa){
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        diff[u]+=diff[v];
    }
    if(diff[u]>=1){
        ans+=sum[u];
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    tarjan(1);

    for(int i=1;i<=n;i++){
        if(!col[i]){
            col[i]=++color;
            sum[color]+=val[i];
            q.push(i);
            while(!q.empty()){
                int u=q.front();
                q.pop();
                for(int ei=head[u];ei;ei=nxt[ei]){
                    int v=to[ei];
                    if(col[v]||bridge[ei]){
                        continue;
                    }
                    col[v]=color;
                    sum[color]+=val[v];
                    q.push(v);
                }
            }
        }
    }

    p=log2(color)+1;

    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(col[v]!=col[u]){
                if(col[v]<col[u]){
                    Addedge(col[v],col[u]);
                    Addedge(col[u],col[v]);
                }
            }
        }
    }

    dfs(1,0);

    int q=read();
    while(q--){
        int a,b;
        a=read(),b=read();
        a=col[a],b=col[b];
        int ablca=lca(a,b);
        diff[a]++,diff[b]++,diff[ablca]--,diff[st[ablca][0]]--;
        // printf("%d\n",diff[a]+diff[b]-diff[ablca]);
    }

    dfs1(1,0);
    
    printf("%d\n",ans);

    return 0;
}