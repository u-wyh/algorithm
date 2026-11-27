// https://www.luogu.com.cn/problem/P9697
// 题意：多组数据（共 T 组）。
// 长度 n 的序列初始全为 0，有 m 个操作：第 i 个操作将第 l_i 个元素改为 x_i，第 r_i 个元素改为 y_i。
// 求一个 1..m 的排列作为操作执行顺序，最大化所有操作执行后序列元素之和。
// 题意：第一行输入 T，每组输入 n, m 及 m 行 (l_i, x_i, r_i, y_i)；
// 每组第一行输出最大元素和，第二行输出执行顺序排列（任一合法最优解）。
// 数据范围：2 <= n, m <= 5 * 10^5，1 <= l_i < r_i <= n，1 <= x_i, y_i <= 2
// sum(n), sum(m) <= 5 * 10^5（未显式给出 T 上界，受 sum(n), sum(m) 限制）。
// 算法标签：Tarjan强连通分量、深度优先搜索
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m;
int l[MAXN],x[MAXN];
int r[MAXN],y[MAXN];

int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,dfncnt;
int col[MAXN];
bool instack[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int weight[MAXN];
int cnt=1;

int in[MAXN];
bool vis[MAXN];

int now,last;
int ans[MAXN];
bool two[MAXN];
int res[MAXN];

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    st[++top]=u;
    instack[u]=true;

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }

    if(dfn[u]==low[u]){
        col[u]=++color;
        while(st[top]!=u){
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[u]=false;
        top--;
    }
}

void init(){
    cnt=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        two[i]=0;
        in[i]=0;
        vis[i]=false;
        dfn[i]=low[i]=0;
    }
    top=0;
    color=0;
    dfncnt=0;
}

void dfs(int u){
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        ans[last--]=w;
        if(!vis[v]){
            dfs(v);
        }
    }
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        init();
        now=0,last=m;
        for(int i=1;i<=m;i++){
            l[i]=read(),x[i]=read();
            r[i]=read(),y[i]=read();

            if(x[i]==2&&y[i]==2){
                ans[last--]=i;
                two[l[i]]=two[r[i]]=true;
            }
            else if(x[i]==1&&y[i]==1){
                ans[++now]=i;
            }
            else{
                if(x[i]>y[i]){
                    swap(x[i],y[i]);
                    swap(l[i],r[i]);
                }
                addedge(l[i],r[i],i);
            }
        }

        for(int u=1;u<=n;u++){
            if(!dfn[u]){
                tarjan(u);
            }
        }

        for(int u=1;u<=n;u++){
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                if(col[u]!=col[v]){
                    in[col[v]]++;
                }
            }
        }

        for(int u=1;u<=n;u++){
            if(in[col[u]]==0&&!vis[u]&&two[u]){
                dfs(u);
            }
        }
        for(int u=1;u<=n;u++){
            if(in[col[u]]==0&&!vis[u]){
                dfs(u);
            }
        }

        for(int i=1;i<=n;i++){
            res[i]=0;
        }
        for(int i=1;i<=m;i++){
            int id=ans[i];
            res[l[id]]=x[id];
            res[r[id]]=y[id];
        }
        int all=0;
        for(int i=1;i<=n;i++){
            all+=res[i];
        }
        cout<<all<<endl;
        for(int i=1;i<=m;i++){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}