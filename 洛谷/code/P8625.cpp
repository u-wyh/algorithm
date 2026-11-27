// https://www.luogu.com.cn/problem/P8625
// 题意：输入整数 n、n 个节点权值和 n-1 条边组成的树，在树中选出一个连通点集 S（允许为空集，空集和为 0），输出 S 中节点权值和的最大值。
// 数据范围：0 < n <= 10^5，每个节点权值的绝对值 <= 10^6。
// 算法标签：树形动态规划、深度优先搜索
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n;
int nums[MAXN];
int edge[MAXN][2];
vector<vector<int >>graph;
long long ans[MAXN],headans[MAXN];

void f(int x,int p){
    for(int i=0;i<graph[x].size();i++){
        int v=graph[x][i];
        if(v!=p){
            f(v,x);
            ans[x]=max(ans[x],ans[v]);
            headans[x]=max(headans[x],headans[x]+headans[v]);
        }
    }
    ans[x]=max(ans[x],headans[x]);
}

int main()
{
    cin>>n;
    graph.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        headans[i]=nums[i];
        //ans[i]=max(0,nums[i]);
    }
    for(int i=1;i<n;i++){
        cin>>edge[i][0]>>edge[i][1];
        graph[edge[i][0]].push_back(edge[i][1]);
        graph[edge[i][1]].push_back(edge[i][0]);
    }
    f(1,0);
    cout<<ans[1];
    return 0;
}
