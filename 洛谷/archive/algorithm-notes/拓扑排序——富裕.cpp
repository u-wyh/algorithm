// 喧闹和富有
// 从 0 到 n - 1 编号，其中每个人都有不同数目的钱，以及不同程度的安静值
// 给你一个数组richer，其中richer[i] = [ai, bi] 表示 
// person ai 比 person bi 更有钱
// 还有一个整数数组 quiet ，其中 quiet[i] 是 person i 的安静值
// richer 中所给出的数据 逻辑自洽
// 也就是说，在 person x 比 person y 更有钱的同时，不会出现
// person y 比 person x 更有钱的情况
// 现在，返回一个整数数组 answer 作为答案，其中 answer[x] = y 的前提是,
// 在所有拥有的钱肯定不少于 person x 的人中，
// person y 是最安静的人（也就是安静值 quiet[y] 最小的人）。
// 测试链接 : https://leetcode.cn/problems/loud-and-rich/
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 250000;
const int MAXN = 500;

int n,m;
vector<vector<int >>graph;
//使用邻接表建图
int edge[MAXM][2];
//输入的边数据
int quiet[MAXN];
//输入的安静数值
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
