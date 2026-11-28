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
// 难度评分：1700（LeetCode 分级参考）
// 算法标签：拓扑排序、动态规划
#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time){
        vector<vector<int>> graph(n);
        vector<int> indegree(n), finish(n);
        for(const auto& edge:relations){
            int u=edge[0]-1;
            int v=edge[1]-1;
            graph[u].push_back(v);
            indegree[v]++;
        }

        queue<int> q;
        for(int i=0;i<n;i++){
            if(indegree[i]==0){
                q.push(i);
            }
        }
        int ans=0;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            finish[u]+=time[u];
            ans=max(ans,finish[u]);
            for(int v:graph[u]){
                finish[v]=max(finish[v],finish[u]);
                if(--indegree[v]==0){
                    q.push(v);
                }
            }
        }
        return ans;
    }
};

#ifndef LEETCODE
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    if(!(cin>>n>>m)){
        return 0;
    }
    vector<vector<int>> relations(m,vector<int>(2));
    vector<int> time(n);
    for(auto& edge:relations){
        cin>>edge[0]>>edge[1];
    }
    for(int& months:time){
        cin>>months;
    }
    Solution solution;
    cout<<solution.minimumTime(n,relations,time)<<'\n';
    return 0;
}
#endif
