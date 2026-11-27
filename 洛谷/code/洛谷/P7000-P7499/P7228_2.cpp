// https://www.luogu.com.cn/problem/P7228
// 题意：给定一棵 N 个点的无向树，为每条边定向，
// 使得有向图中的最长有向路径长度最小，
// 输出任意一种定向方案（1 表示 a_i -> b_i
// 0 表示 b_i -> a_i）。
// 数据范围：2 <= N <= 10^5，1 <= a_i, b_i <= N。
// 算法标签：深度优先搜索、构造
#include<iostream>
#define endl '\n'
using namespace std;
#define MAXN 100001
int n;
struct edge{
    int v;
    int next;
}e[MAXN<<1];
int head[MAXN];
bool towards[MAXN];//确认边要不要调换方向
bool f=0;//初始为0或1都没关系
bool vis[MAXN];
void dfs(int p)
{
    if(vis[p])
        return;
    vis[p]=1;
    f^=1;
    for(int i=head[p];i;i=e[i].next)
    {
        if(vis[e[i].v])
            continue;
        //f^=1;
        if(i>MAXN)
            towards[i-MAXN]=f^1;
        else
            towards[i]=f;
        dfs(e[i].v);
        //f^=1;
    }
    f^=1;
}
int main()
{
    cin>>n;
    for(int i=1,j=MAXN+1,u,v;i<n;i++,j++)
    {
        cin>>u>>v;
        e[i].v=v,e[i].next=head[u],head[u]=i;//加边
        e[j].v=u,e[j].next=head[v],head[v]=j;//无向图加反向边
    }
    dfs(1);
    for(int i=1;i<n;i++)
        cout<<towards[i]<<endl;
    return 0;
}
