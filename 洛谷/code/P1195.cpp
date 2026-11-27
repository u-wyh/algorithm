// https://www.luogu.com.cn/problem/P1195
// 题意：给定 N 朵云及 M 条可合并关系，每条关系连接两朵云并消耗代价 L。
// 题意：要求把所有云朵连成恰好 K 个连通块（每块至少一朵云），求最小总代价。
// 输入：第一行输入 N, M, K，接下来 M 行每行输入 X, Y, L。
// 输出：输出最小代价；若无法连成 K 个连通块，输出 No Answer。
// 数据范围：1 <= N <= 10^3，1 <= M <= 10^4，1 <= K <= 10。
// 数据范围：1 <= X, Y <= N，0 <= L < 10^4。
#include<bits/stdc++.h>
#define N 1005
// 算法标签：最小生成树、Kruskal、并查集
using namespace std;
int n,m,k,x,y,l,sum,ans;
int fa[N];
struct Edge
{
    int u,v,w;
    bool operator <(Edge a) const
    {
        return w<a.w;
    }
}edge[N*10];
int find(int x)
{
    return fa[x]==x?fa[x]:fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    }
    sort(edge+1,edge+m+1);
    for(int i=1;i<=m;i++)
    {
        int fx=find(edge[i].u),fy=find(edge[i].v);
        if(fx!=fy)
        {
            fa[fx]=fy;
            sum++;
            ans+=edge[i].w;
        }
        if(sum==n-k)
        {
            printf("%d",ans);
            return 0;
        }
    }
    puts("No Answer");
    return 0;
}
