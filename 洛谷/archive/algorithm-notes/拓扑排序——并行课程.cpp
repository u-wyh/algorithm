// 并行课程 III
// 给你一个整数 n ，表示有 n 节课，课程编号从 1 到 n
// 同时给你一个二维整数数组 relations ，
// 其中 relations[j] = [prevCoursej, nextCoursej]
// 表示课程 prevCoursej 必须在课程 nextCoursej 之前 完成（先修课的关系）
// 同时给你一个下标从 0 开始的整数数组 time
// 其中 time[i] 表示完成第 (i+1) 门课程需要花费的 月份 数。
// 请你根据以下规则算出完成所有课程所需要的 最少 月份数：
// 如果一门课的所有先修课都已经完成，你可以在 任意 时间开始这门课程。
// 你可以 同时 上 任意门课程 。请你返回完成所有课程所需要的 最少 月份数。
// 注意：测试数据保证一定可以完成所有课程（也就是先修课的关系构成一个有向无环图）
// 测试链接 : https://leetcode.cn/problems/parallel-courses-iii/
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 250000;
const int MAXN = 500;

int n,m;
vector<vector<int >>graph;
//使用邻接表建图
int edge[MAXM][2];
//输入的边数据
int Time[MAXN];
//输入的安静数值
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

