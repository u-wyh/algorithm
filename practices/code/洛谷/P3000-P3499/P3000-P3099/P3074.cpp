// https://www.luogu.com.cn/problem/P3074
// 题意：输入奶牛数量 N、约束数量 M，每头牛的挤奶耗时 T_i，
// 以及 M 条先后约束 (A, B)。
// 若有约束 (A, B)，
// 则必须等奶牛 A 完全挤奶结束后才能开始给奶牛 B 挤奶，
// 无约束的奶牛可同时挤奶。
// 保证约束关系构成有向无环图，求完成所有奶牛挤奶的最短总时间。
// 输出一个整数表示最短总时间。
// 数据范围：1 <= N <= 10^4，1 <= M <= 5*10^4，
// 1 <= T_i <= 10^5。
// 难度评分：1400（洛谷分级换算）
// 算法标签：拓扑排序、动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int MAXM = 50005;

int n,m;
int Time[MAXN];
int cost[MAXN];
int indegree[MAXN];
int u,v;
int  ans=0;
vector<vector<int >>graph;
queue<int >q;

int main()
{
    cin>>n>>m;
    graph.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>Time[i];
    }
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        graph[u].push_back(v);
        indegree[v]++;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        cost[cur]+=Time[cur];
        ans=max(ans,cost[cur]);
        for(int i=0;i<graph[cur].size();i++){
            indegree[graph[cur][i]]--;
            cost[graph[cur][i]]=max(cost[cur],cost[graph[cur][i]]);
            if(indegree[graph[cur][i]]==0){
                q.push(graph[cur][i]);
            }
        }
    }
    cout<<ans;
    return 0;
}
