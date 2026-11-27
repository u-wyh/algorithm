// https://www.luogu.com.cn/problem/P3063
// 题意：输入连接点数 N、双向管道数 M、总牛奶量 X，以及 M 条连接 (I, J) 的管道延迟 L 和容量 C（可能有重边，牛棚在 1，储存罐在 N）。
// 一条从 1 到 N 的路径总延迟为沿途管道延迟之和 L_path，总容量为沿途管道容量最小值 C_min
// 输送 X 单位牛奶的总时间为 L_path + X / C_min。
// 选出一条从 1 到 N 的路径使总时间最小，并将最小总时间向下取整到整数。
// 输出一行一个整数，表示最少时间向下取整后的结果。
// 数据范围：对于 100% 的数据，1 <= N <= 500，1 <= M <= 500，1 <= X <= 10^6，1 <= I, J <= N
// 1 <= L, C <= 10^6。
#include<bits/stdc++.h>
// 算法标签：深度优先搜索、剪枝
using namespace std;
const int MAXN = 505;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int val[MAXN<<1];
int cnt=1;
int n,m,k;
int vis[MAXN][MAXN];
int ans=INT_MAX;

void addedge(int u,int v,int w,int y){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    val[cnt]=y;
    head[u]=cnt++;
}

void dfs(int u,int w,int v){
    if(w+v>ans){
        return ;
    }
    if(u==n){
        ans=min(ans,w+v);
    }
    for(int i=head[u];i;i=Next[i]){
        int e=to[i];
        if(vis[u][e])
            continue;
        vis[u][e]=1;
        dfs(e,w+weight[i],max(v,val[i]));
        vis[u][e]=0;
    }
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,w,y;
        cin>>u>>v>>w>>y;
        addedge(u,v,w,k/y);
        addedge(v,u,w,k/y);
    }
    dfs(1,0,0);
    cout<<ans<<endl;
    return 0;
}
