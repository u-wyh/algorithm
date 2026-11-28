// https://leetcode.cn/problems/loud-and-rich/
// 题意：给每个人的安静值 quiet，
// 以及富有关系 richer，其中 [a, b] 表示 a 比 b 富有。
// 对每个人 x，从能确定钱不少于 x 的人中，
// 选出 quiet 值最小的人，可以选 x 本人。
// 输出：返回所有 x 对应的人物编号。
// 数据范围：1 <= n <= 500，quiet 的长度为 n。
// 0 <= quiet[i] < n，安静值互不相同。
// 关系数为 0 到 n*(n-1)/2，关系互异且无环。
// 0 <= a, b < n，a != b。
// 难度评分：1500（LeetCode 分级参考）
// 算法标签：拓扑排序、动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 250000;
const int MAXN = 500;

int n,m;
vector<vector<int >>graph;
//使用邻接表建图
int edge[MAXM][2];
int quiet[MAXN];
int indegree[MAXN];
//各个节点的入度
int ans[MAXN];
//每个节点的答案
queue<int>q;

int main()
{
    cin>>n>>m;
    graph.resize(n);//初始化动态数组大小
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1];
    }
    for(int i=0;i<n;i++){
        cin>>quiet[i];
    }
    for(int i=1;i<=m;i++){
        graph[edge[i][0]].push_back(edge[i][1]);
        //建图
        indegree[edge[i][1]]++;
        //增加入度
    }
    for(int i=0;i<n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    for(int i=0;i<n;i++){
        ans[i]=i;
        //首先将每个节点答案初始化为本身
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<graph[cur].size();i++){
            //将这个即将出去的节点所有功能结算
            if(quiet[ans[graph[cur][i]]]>quiet[ans[cur]]){
                //它所指向的节点一定不如自己有钱 尝试自己能否更新他的答案
                ans[graph[cur][i]]=ans[cur];
            }
            indegree[graph[cur][i]]--;
            if(indegree[graph[cur][i]]==0){
                q.push(graph[cur][i]);
            }
        }
    }
    for(int i=0;i<n;i++){
        printf("%3d",ans[i]);
    }
    return 0;
}
