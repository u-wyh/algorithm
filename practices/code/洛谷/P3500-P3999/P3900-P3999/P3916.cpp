// https://www.luogu.com.cn/problem/P3916
// 题意：给定 N 个点 M 条边的有向图，对每个点 v（1..N），
// 求从 v 出发能够到达的编号最大的节点编号 A(v)。
// 数据范围：1 <= N, M <= 10^5。
// 难度评分：1300（洛谷分级换算）
// 算法标签：深度优先搜索、反向建图
#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<int > p[100005];
int a[100005];

void dfs(int x,int y){
    a[x]=y;
    for(int i=0;i<p[x].size();i++){
        if(a[p[x][i]]==0){
            dfs(p[x][i],y);
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        p[v].push_back(u);
    }
    for(int i=n;i>0;i--){
        if(a[i]==0){
            dfs(i,i);
        }
    }
    for(int i=1;i<=n;i++)
        cout<<a[i]<<' ';
    return 0;
}
