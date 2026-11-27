// https://leetcode.cn/problems/parallel-courses-iii/
// 题意：给 n 门课程的耗时 time 和先修关系 relations。
// 关系 [u, v] 表示须完成课程 u 才能开始 v。
// 任何课程的先修课都完成后即可开课。
// 每月可同时修读任意多门满足条件的课程。
// 输出：返回完成所有课程所需的最少月份数。
// 数据范围：1 <= n <= 5*10^4，time 长度为 n。
// 关系数为 0 到 min(n*(n-1)/2, 5*10^4)。
// 1 <= u, v <= n，关系互异且无环。
// 1 <= time[i] <= 10^4。
// 算法标签：拓扑排序、动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 250000;
const int MAXN = 500;

int n,m;
vector<vector<int >>graph;
//使用邻接表建图
int edge[MAXM][2];
int Time[MAXN];
int indegree[MAXN];
//各个节点的入度
int ans[MAXN];
//每个节点的答案
queue<int>q;
int maxans=0;

int main()
{
    cin>>n>>m;
    graph.resize(n+1);//初始化动态数组大小
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1];
    }
    for(int i=1;i<=n;i++){
        cin>>Time[i];
    }
    for(int i=1;i<=m;i++){
        graph[edge[i][0]].push_back(edge[i][1]);
        //建图
        indegree[edge[i][1]]++;
        //增加入度
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        ans[cur]+=Time[cur];
        maxans=max(maxans,ans[cur]);
        q.pop();
        for(int i=0;i<graph[cur].size();i++){
            ans[graph[cur][i]]=max(ans[graph[cur][i]],ans[cur]);
            //将这个即将出去的节点所有功能结算
            indegree[graph[cur][i]]--;
            if(indegree[graph[cur][i]]==0){
                q.push(graph[cur][i]);
            }
        }
    }
    cout<<maxans;
    return 0;
}

