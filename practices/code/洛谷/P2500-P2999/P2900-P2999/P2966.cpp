// https://www.luogu.com.cn/problem/P2966
// 题意：输入牧场数 N、无向边数 M、询问数 Q，
// 每个点的过路费 C_i，M 条无向边
// (A_i, B_i, L_i)（无自环、连通、可能有重边）
// 以及 Q 组起终点查询 (s_i, t_i)。
// 一条路径的总费用定义为：沿途所有边权 L 之和，
// 加上沿途经过的所有点（含起点和终点）中点权 C 的最大值。
// 对每组询问，求出从 s_i 到 t_i 的最小总费用。
// 输出共 Q 行，每行一个整数表示对应询问的最小费用。
// 数据范围：对于 100% 的数据，1 <= N <= 250，
// 1 <= M <= 10^4，1 <= Q <= 10^4，
// 1 <= C_i <= 10^5
// 1 <= L_j <= 10^5。
//P2966
// Floyd中G[i][j]实际上是一个滚动数组，
// 真正的DP数组是G[k][i][j]，
//其中k是阶段.G[k][i][j]表示只经过1~k这些节点，i到j的最短距离
//这道题考察的就是他的这个含义
// 我们将点权按照权值大小排序  那么解决点权问题就
// 可以用i j k的权值大小来排序了
// 难度评分：1800（洛谷分级换算）
// 算法标签：Floyd、最短路、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 255;
const int MAXM = 1e4+5;
const int INF = 1e9;

int n,m,k;
struct node{
    int val,sub;
}nums[MAXN];
int dis[MAXN][MAXN];
int ans[MAXN][MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

bool cmp(node a,node b){
    return a.val<b.val;
}

void floyd(){
    for(int k=1;k<=n;k++){
        //表示只经历1到k这些节点作为中间节点的情况
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int u=nums[i].sub,v=nums[j].sub,w=nums[k].sub;
                dis[u][v]=min(dis[u][v],dis[u][w]+dis[w][v]);
                ans[u][v]=min(ans[u][v],dis[u][v]+max(nums[i].val,max(nums[j].val,nums[k].val)));
            }
        }
    }
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++){
        nums[i].sub=i;
        cin>>nums[i].val;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)
                dis[i][j]=0;
            else
                dis[i][j]=INF;
            ans[i][j]=INF;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=dis[v][u]=min(dis[u][v],w);
    }
    floyd();
    for(int i=1;i<=k;i++){
        int u,v;
        cin>>u>>v;
        cout<<ans[u][v]<<endl;
    }
    return 0;
}