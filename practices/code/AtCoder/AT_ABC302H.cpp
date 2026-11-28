// https://atcoder.jp/contests/abc302/tasks/abc302_h
// 题意：给定 N 点的树，每点有编号为 A_i、B_i 的两个球。
// 对每个 v = 2..N，从 1 到 v 的路径上每点选一个球。
// 输出：按 v 递增输出可选出的不同编号种数的最大值。
// 数据范围：2 <= N <= 2*10^5，
// 1 <= A_i, B_i <= N。
// 难度评分：2400（AtCoder Problems 换算）
// 算法标签：可撤销并查集、深度优先搜索
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;

int arr[MAXN][2];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];

int fa[MAXN];
int sz[MAXN];
int edge[MAXN];

int sta[MAXN][2];
int top;

int now=0;
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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int find(int x){
    int f=fa[x];
    while(x!=f){
        x=f;
        f=fa[x];
    }
    return x;
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy){
        return ;
    }
    if(sz[fx]<sz[fy]){
        swap(fx,fy);
    }
    sta[++top][0]=fx;
    sta[top][1]=fy;

    sz[fx]+=sz[fy];
    fa[fy]=fx;
    edge[fx]+=1+edge[fy];
}

void undo(){
    int fx=sta[top][0];
    int fy=sta[top--][1];
    fa[fy]=fy;
    sz[fx]-=sz[fy];
    edge[fx]-=edge[fy]+1;
}

void dfs(int u,int fa){
    int fx=find(arr[u][0]);
    int fy=find(arr[u][1]);
    bool add=false;
    bool uni=false;
    if(fx==fy){
        if(edge[fx]<sz[fx]){
            add=true;
            now++;
        }
        edge[fx]++;
    }
    else{
        if(sz[fx]>edge[fx]||sz[fy]>edge[fy]){
            now++;
            add=true;
        }
        un(fx,fy);
        uni=true;
    }

    ans[u]=now;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
    }

    if(add){
        now--;
    }
    if(uni){
        undo();
    }
    else{
        edge[fx]--;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        arr[i][0]=read(),arr[i][1]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v),addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    dfs(1,0);
    for(int i=2;i<=n;i++){
        printf("%d ",ans[i]);
    }
    return 0;
}