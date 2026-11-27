// https://www.luogu.com.cn/problem/P5318
// 题意：给定一个 n 点 m 边的有向图，从 1 号点出发分别做 DFS 和 BFS 遍历。
// 若有多个后继节点可选，优先访问编号更小的节点，输出两行遍历序。
// 数据范围：1 <= n <= 10^5，1 <= m <= 10^6。
#include<bits/stdc++.h>
// 算法标签：深度优先搜索、广度优先搜索
using namespace std;

int n,m;
vector<int > p[1000005];
queue<int > q;
int vis1[1000005],vis2[1000005];

void dfs(int x){
    cout<<x<<' ';
    for(int i=0,sz=p[x].size();i<sz;i++){
        if(!vis1[p[x][i]]){
            vis1[p[x][i]]=1;
            dfs(p[x][i]);
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        p[x].push_back(y);
    }
    vis1[1]=1;
    dfs(1);
    printf("\n");
    vis2[1]=1;
    q.push(1);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        cout<<x<<' ';
        for(int i=0,sz=p[x].size();i<sz;i++){
            if(!vis2[p[x][i]]){
                vis2[p[x][i]]=1;
                q.push(p[x][i]);
            }
        }
    }
    return 0;
}
